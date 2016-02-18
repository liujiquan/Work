
/* Command line parsing with optional Wildcard expansion */
/* identical in function to CRT console startup code     */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CmdLine.h"

#define _T(x) x

/* Globals */

int argc;
char **argv;


// Use Wildcard expansion on Command Line

#define WILDCARD 1


static int mysetargv (char *lpszCmdLine);



// =======================================================================
// ParseCommandLine()
//
// Returns: TRUE if successful, or FALSE if there was an error.
// =======================================================================
int ParseCommandLine(LPTSTR cmdline)
{
	if (mysetargv(cmdline))
		return 0;

	// Returning TRUE means the caller should continue doing what they
	// were doing: we succeeded.
	return 1;
}


void FreeCommandLine(void)
{
}



/***
*wild.c - wildcard expander
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*        expands wildcards in argv
*
*        handles '*' (none or more of any char) and '?' (exactly one char)
*
*******************************************************************************/

/*
** these are the data structures
**
**     __argv
**     -------     ------
**     |     |---->|    |---->"arg0"
**     -------     ------
**                 |    |---->"arg1"
**                 ------
**                  ....
**                 ------
**                 |    |---->"argn"
**                 ------
**                 |NULL|
**                 ------
**                                       argend
**                                       -------
**     -------                           |     |
**     |     | __argc                    -------
**     -------                              |
**                                          |
**  arghead                                 V
**  ------     ---------                ----------
**  |    |---->|   |   |----> .... ---->|   |NULL|
**  ------     ---------                ----------
**               |                        |
**               V                        V
**            "narg0"                  "nargn"
*/



/* Prototypes */

struct argnode {
    char *argptr;
    struct argnode *nextnode;
};

static int mycwild (void);
static int mymatch(char *, char *);
static int myadd(char *);
static void mysort(struct argnode *);
static char * myfind (char *pattern);
static void myparse_cmdline(char *cmdstart, char **argv, char *args,
        int *numargs, int *numchars);

        
#define NULCHAR         _T('\0')
#define SPACECHAR       _T(' ')
#define TABCHAR         _T('\t')
#define DQUOTECHAR      _T('\"')
#define SLASHCHAR       _T('\\')

#define FWDSLASHCHAR    _T('/')
#define COLONCHAR       _T(':')
#define QUOTECHAR       _T('\"')

#define SLASH           _T("\\")
#define FWDSLASH        _T("/")
#define STAR            _T("*.*")
#define DOT             _T(".")
#define DOTDOT          _T("..")

#define WILDSTRING      _T("*?")


static struct argnode *arghead;
static struct argnode *argend;




/***
*stdargv.c - standard & wildcard _setargv routine
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       processes program command line, with or without wildcard expansion
*
*******************************************************************************/



/***
*_setargv, __setargv - set up "argc" and "argv" for C programs
*
*Purpose:
*       Read the command line and create the argv array for C
*       programs.
*
*Entry:
*       Arguments are retrieved from the program command line,
*       pointed to by _acmdln.
*
*Exit:
*       "argv" points to a null-terminated list of pointers to ASCIZ
*       strings, each of which is an argument from the command line.
*       "argc" is the number of arguments.  The strings are copied from
*       the environment segment into space allocated on the heap/stack.
*       The list of pointers is also located on the heap or stack.
*       _pgmptr points to the program name.
*
*Exceptions:
*       Terminates with out of memory error if no memory to allocate.
*
*******************************************************************************/

static int mysetargv (char *lpszCmdLine)
{
        char *p;
        char *cmdstart;                  /* start of command line to parse */
        int numargs, numchars;

        /* if there's no command line at all (won't happen from cmd.exe, but
           possibly another program), then we use _pgmptr as the command line
           to parse, so that argv[0] is initialized to the program name */

        cmdstart = lpszCmdLine;

        /* first find out how much space is needed to store args */
        myparse_cmdline(cmdstart, NULL, NULL, &numargs, &numchars);

        /* allocate space for argv[] vector and strings */
        p = (char*)malloc(numargs * sizeof(char *) + numchars);
        if (p == NULL)
            return(-1);

        /* store args and argv ptrs in just allocated block */

        myparse_cmdline(cmdstart, (char **)p, p + numargs * sizeof(char *), &numargs, &numchars);

        /* set argv and argc */
        argc = numargs - 1;
        argv = (char **)p;

#ifdef WILDCARD

        /* call _[w]cwild to expand wildcards in arg vector */
        if (mycwild())
            return(-1);

#endif  /* WILDCARD */
		return(0);
}


/***
*static void parse_cmdline(cmdstart, argv, args, numargs, numchars)
*
*Purpose:
*       Parses the command line and sets up the argv[] array.
*       On entry, cmdstart should point to the command line,
*       argv should point to memory for the argv array, args
*       points to memory to place the text of the arguments.
*       If these are NULL, then no storing (only coujting)
*       is done.  On exit, *numargs has the number of
*       arguments (plus one for a final NULL argument),
*       and *numchars has the number of bytes used in the buffer
*       pointed to by args.
*
*Entry:
*       char *cmdstart - pointer to command line of the form
*           <progname><nul><args><nul>
*       char **argv - where to build argv array; NULL means don't
*                       build array
*       char *args - where to place argument text; NULL means don't
*                       store text
*
*Exit:
*       no return value
*       int *numargs - returns number of argv entries created
*       int *numchars - number of characters used in args buffer
*
*Exceptions:
*
*******************************************************************************/

static void myparse_cmdline (
    char *cmdstart,
    char **argv,
    char *args,
    int *numargs,
    int *numchars
    )
{
        char *p;
        char c;
        int inquote;                    /* 1 = inside quotes */
        int copychar;                   /* 1 = copy char to *args */
        unsigned numslash;              /* num of backslashes seen */

        *numchars = 0;
        *numargs = 1;                   /* the program name at least */

        /* first scan the program name, copy it, and count the bytes */
        p = cmdstart;
        if (argv)
            *argv++ = args;

#ifdef WILDCARD
        /* To handle later wild card expansion, we prefix each entry by
        it's first character before quote handling.  This is done
        so _[w]cwild() knows whether to expand an entry or not. */
        if (args)
            *args++ = *p;
        ++*numchars;

#endif  /* WILDCARD */

        /* A quoted program name is handled here. The handling is much
           simpler than for other arguments. Basically, whatever lies
           between the leading double-quote and next one, or a terminal null
           character is simply accepted. Fancier handling is not required
           because the program name must be a legal NTFS/HPFS file name.
           Note that the double-quote characters are not copied, nor do they
           contribute to numchars. */
        if ( *p == DQUOTECHAR ) {
            /* scan from just past the first double-quote through the next
               double-quote, or up to a null, whichever comes first */
            while ( (*(++p) != DQUOTECHAR) && (*p != NULCHAR) ) {

                ++*numchars;
                if ( args )
                    *args++ = *p;
            }
            /* append the terminating null */
            ++*numchars;
            if ( args )
                *args++ = NULCHAR;

            /* if we stopped on a double-quote (usual case), skip over it */
            if ( *p == DQUOTECHAR )
                p++;
        }
        else {
            /* Not a quoted program name */
            do {
                ++*numchars;
                if (args)
                    *args++ = *p;

                c = *p++;

            } while ( c != SPACECHAR && c != NULCHAR && c != TABCHAR );

            if ( c == NULCHAR ) {
                p--;
            } else {
                if (args)
                    *(args-1) = NULCHAR;
            }
        }

        inquote = 0;

        /* loop on each argument */
        for(;;) {

            if ( *p ) {
                while (*p == SPACECHAR || *p == TABCHAR)
                    ++p;
            }

            if (*p == NULCHAR)
                break;              /* end of args */

            /* scan an argument */
            if (argv)
                *argv++ = args;     /* store ptr to arg */
            ++*numargs;

#ifdef WILDCARD
        /* To handle later wild card expansion, we prefix each entry by
        it's first character before quote handling.  This is done
        so _[w]cwild() knows whether to expand an entry or not. */
        if (args)
            *args++ = *p;
        ++*numchars;

#endif  /* WILDCARD */

        /* loop through scanning one argument */
        for (;;) {
            copychar = 1;
            /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
               2N+1 backslashes + " ==> N backslashes + literal "
               N backslashes ==> N backslashes */
            numslash = 0;
            while (*p == SLASHCHAR) {
                /* count number of backslashes for use below */
                ++p;
                ++numslash;
            }
            if (*p == DQUOTECHAR) {
                /* if 2N backslashes before, start/end quote, otherwise
                    copy literally */
                if (numslash % 2 == 0) {
                    if (inquote) {
                        if (p[1] == DQUOTECHAR)
                            p++;    /* Double quote inside quoted string */
                        else        /* skip first quote char and copy second */
                            copychar = 0;
                    } else
                        copychar = 0;       /* don't copy quote */

                    inquote = !inquote;
                }
                numslash /= 2;          /* divide numslash by two */
            }

            /* copy slashes */
            while (numslash--) {
                if (args)
                    *args++ = SLASHCHAR;
                ++*numchars;
            }

            /* if at end of arg, break loop */
            if (*p == NULCHAR || (!inquote && (*p == SPACECHAR || *p == TABCHAR)))
                break;

            /* copy character into argument */
            if (copychar) {
                if (args)
                    *args++ = *p;
                ++*numchars;
            }
            ++p;
            }

            /* null-terminate the argument */

            if (args)
                *args++ = NULCHAR;          /* terminate string */
            ++*numchars;
        }

        /* We put one last argument in -- a null ptr */
        if (argv)
            *argv++ = NULL;
        ++*numargs;
}


/***
*int _cwild() - wildcard expander
*
*Purpose:
*    expands wildcard in file specs in argv
*
*    handles '*' (none or more of any char), '?' (exactly one char), and
*    '[string]' (chars which match string chars or between n1 and n2
*    if 'n1-n2' in string inclusive)
*
*Entry:
*
*Exit:
*    returns 0 if successful, -1 if any malloc() calls fail
*    if problems with malloc, the old argc and argv are not touched
*
*Exceptions:
*
*******************************************************************************/

int mycwild (void)
{
    char **newargv = argv;
    struct argnode *nodeptr;
    int newargc;
    char **tmp;
    char *wchar;

    arghead = argend = NULL;

    for (newargv = argv; *newargv; newargv++)  /* for each arg... */
        if ( *(*newargv)++ == QUOTECHAR )
            /* strip leading quote from quoted arg */
        {
            if (myadd(*newargv))
                return(-1);
        }
        else if (wchar = strpbrk( *newargv, WILDSTRING )) {
            /* attempt to expand arg with wildcard */
            if (mymatch( *newargv, wchar ))
                return(-1);
        }
        else if (myadd( *newargv )) /* normal arg, just add */
            return(-1);

    /* count the args */
    for (newargc = 0, nodeptr = arghead; nodeptr;
            nodeptr = nodeptr->nextnode, newargc++)
            ;

    /* try to get new arg vector */
    if (!(tmp = (char **)malloc(sizeof(char *)*(newargc+1))))
        return(-1);

    /* the new arg vector... */
    argv = tmp;

    /* the new arg count... */
    argc = newargc;

    /* install the new args */
    for (nodeptr = arghead; nodeptr; nodeptr = nodeptr->nextnode)
        *tmp++ = nodeptr->argptr;

    /* the terminal NULL */
    *tmp = NULL;

    /* free up local data */
    for (nodeptr = arghead; nodeptr; nodeptr = arghead) {
        arghead = arghead->nextnode;
        free(nodeptr);
    }

    /* return success */
    return(0);
}


/***
*match(arg, ptr) - [STATIC]
*
*Purpose:
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

static int mymatch (char *arg, char *ptr)
{
    char *cnew;
    int length = 0;
    char *all;
    struct argnode *first;
    int gotone = 0;

    while (ptr != arg && *ptr != SLASHCHAR && *ptr != FWDSLASHCHAR
        && *ptr != COLONCHAR) {
        /* find first slash or ':' before wildcard */
        ptr--;
    }

    if (*ptr == COLONCHAR && ptr != arg+1) /* weird name, just add it as is */
        return(myadd(arg));

    if (*ptr == SLASHCHAR || *ptr == FWDSLASHCHAR
        || *ptr == COLONCHAR) /* pathname */
        length = ptr - arg + 1; /* length of dir prefix */

    if (cnew = myfind(arg)) { /* get the first file name */
        first = argend;

        do  { /* got a file name */
            if (strcmp(cnew, DOT) && strcmp(cnew, DOTDOT)) {
                if (*ptr != SLASHCHAR && *ptr != COLONCHAR
                    && *ptr != FWDSLASHCHAR ) {
                    /* current directory; don't need path */
#ifdef _DEBUG
                    if (!(arg=(char*)malloc((strlen(cnew)+1)))
                        || myadd(strcpy(arg,cnew)))
#else  /* _DEBUG */
                    if (!(arg = strdup(cnew)) || myadd(arg))
#endif  /* _DEBUG */
                        return(-1);
                }
                else    /* add full pathname */
                    if (!(all=(char*)malloc((length+strlen(cnew)+1)))
                        || myadd(strcpy(strncpy(all,arg,length)+length,cnew)
                        - length))
                        return(-1);

                gotone++;
            }

        }
        while (cnew = myfind(NULL));  /* get following files */

        if (gotone) {
            mysort(first ? first->nextnode : arghead);
            return(0);
        }
    }

    return(myadd(arg)); /* no match */
}

/***
*add(arg) - [STATIC]
*
*Purpose:
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

static int myadd ( char *arg )
{
    struct argnode *nodeptr;

    if (!(nodeptr = (struct argnode *)malloc(sizeof(struct argnode))))
        return(-1);

    nodeptr->argptr = arg;
    nodeptr->nextnode = NULL;

    if (arghead)
        argend->nextnode = nodeptr;
    else
        arghead = nodeptr;

    argend = nodeptr;
    return(0);
}


/***
*sort(first) - [STATIC]
*
*Purpose:
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

static void mysort (struct argnode *first)
{
    struct argnode *nodeptr;
    char *temp;

    if (first) /* something to sort */
        while (nodeptr = first->nextnode) {
            do  {
                if (stricmp(nodeptr->argptr, first->argptr) < 0) {
                    temp = first->argptr;
                    first->argptr = nodeptr->argptr;
                    nodeptr->argptr = temp;
                }
            }
            while (nodeptr = nodeptr->nextnode);

            first = first->nextnode;
        }
}


/***
*find(pattern) - find matching filename
*
*Purpose:
*       if argument is non-null, do a DOSFINDFIRST on that pattern
*       otherwise do a DOSFINDNEXT call.  Return matching filename
*       or NULL if no more matches.
*
*Entry:
*       pattern = pointer to pattern or NULL
*           (NULL means find next matching filename)
*
*Exit:
*       returns pointer to matching file name
*           or NULL if no more matches.
*
*Exceptions:
*
*******************************************************************************/

static char * myfind (char *pattern)
{
        char *retval;

        static HANDLE _WildFindHandle;
        static LPWIN32_FIND_DATA findbuf;

        if (pattern) {
            if (findbuf == NULL)
                findbuf = (LPWIN32_FIND_DATA)malloc(MAX_PATH + sizeof(*findbuf));

            if (_WildFindHandle != NULL) {
                (void)FindClose( _WildFindHandle );
                _WildFindHandle = NULL;
            }

            _WildFindHandle = FindFirstFile( (LPTSTR)pattern, findbuf );
            if (_WildFindHandle == (HANDLE)0xffffffff)
                return NULL;
        }
        else if (!FindNextFile( _WildFindHandle, findbuf )) {
            (void)FindClose( _WildFindHandle );
            _WildFindHandle = NULL;
            return NULL;
        }

        retval = findbuf->cFileName;

        return retval;
}
