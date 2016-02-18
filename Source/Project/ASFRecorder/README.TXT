
============================================================================
=                                                                          =
======   ASFRecorder V1.1 - STILL DOWNLOADING STREAMING CONTENT! ;-)  ======
=                                                                          =
============================================================================

                         Thank you for reading this!
                         
                           Reading makes you smart.
                     Smart people don't have dumb questions.
                If you still have problems, ask fellow users at 
                     http://pub18.ezboard.com/basfrecorder


This  is  an  update - or "service release" to ASFRecorder V1.0.  If you are
new  to  this  software  and  do  not know its features, then skip the first
section and start with the "General Announcements" section.


----------------------------------------------------------------------------
                               News ticker
----------------------------------------------------------------------------
Microsoft has just released version 8 of their audio and video codecs.  This
makes  me expect  us to see a much improved  audio and video quality in many
broadband video clips soon. This is yet another reason  why providers should
really start to use DRM to protect their rights NOW!!!
----------------------------------------------------------------------------




----------------------------------------------------------------------------
                           What's new to V1.1 ?
----------------------------------------------------------------------------

The  most  important "news" is that this is going to be the FINAL RELEASE of
this  software.   No  further  updates  and  fixes  will be performed by the
original author.  It is very likely that I will decide to even shut down the
home page in a few months.

* ASFRecorder  V1.1 now  has a HTTP proxy support (fully configurable in the
  GUI).

* Support for accessing password-protected streams has been added.  Username
  and password must be known, of course. Don't use stolen passwords! This is
  illegal.

* ASFRecorder  now  saves  live-content  as  fully  seekable streams  (which
  unfortunately  only  works correctly with Media Player 6.4, and *not* with
  version 7.0). See the FAQ on how to use Media Player 6.4  even if you have
  previously installed the 7.0 update!

* An  incompatibility  with  certain  streams using  a packetized or "split"
  header has been fixed (which occurs in some audio-only streams using small
  packets, e.g.  audio books or narrow band radio).

* Resuming an incomplete stream will no  longer result in corrupt streams if
  ASFRecorder has previously been  terminated by a system crash or a "forced
  close" of the Windows DOS box.

* ASFRecorder V1.0 transmitted a static client GUID to the media server when
  connecting.   This  has been replaced by a randomized GUID.  So the server
  log  files  can  no  longer  be  specifically  scanned  for  accesses with
  ASFRecorder.

* Handling of %-Escape sequences  in URLs is now done properly (I hope). The
  program now removes disallowed characters from file names (for the Windows
  platform).

* And finally, the "About Box" has been brushed up a little.

By  the way, it took no longer than three days to implement the new features
and  update the documentation.  I almost forgot:  There's a new "episode" of
Star Trek Voyager in the header of asfrecorder.c ;-)

Please  note  that command line arguments have become case-sensitive in this
program version (to allow to distinguish between the -p and -P options).



----------------------------------------------------------------------------
               What has happened since the release of V1.0 ?
----------------------------------------------------------------------------

This  product  has  found  some quite impressive media echo.  The German c't
magazine  (that  is _the_ computer magazine for technically skilled users in
Germany)  featured  this  programm  on  a  full  page.   ZDFMSNBC (german TV
homepage,  in  cooperation with MSN) published a huge online-article on this
program,   including   a  statement  of  a  Microsoft  spokesman  which  was
hillariously funny to read.

The  home  page  of  ASFRecorder  is  striving towards 100,000 hits since it
opened  in  mid  of 2000.  And this is remarkable for a poorly designed home
page  with  static content.  The program is listed on dozens of freeware and
software pages throughout the world.  Several "fans" have created mirrors of
my  home  page  or  even  designed  tutorial  and instruction pages for this
software.   Even  Linux  user  groups  (e.g.   FreshMeat)  have  listed this
software in their archive.

What  I  personally  consider  most  funny is that when I look at the access
logfiles,  I  find  that  employees  of  companies  like  Walt Disney, NASA,
Fujitsu,  Lucent,  Siemens,  Microsoft, etc. have visited my site.  Hey, the
NASA  and  even  Microsoft is using my program - so it must be good.  ;-) By
the  way,  if  I  had  intended  to  smuggle  a  backdoor or trojan into the
Microsoft  campus, I probably would have succeeded.  Hmmm, excessive private
surfing  at  the  work place is in fact a problem - but not my problem.  ;-)
Just to make that point clear:  My ASFRecorder distribution does not contain
a virus, backdoor or trojan, which  you can also  verify  by  looking at the
source code and by applying a virus scanner.

Any reactions from the Industry?

Well,  both  the US patent office and the German patents office took a sneek
on  the  homepage,  but  that's  it.   No  further reactions.  The home page
mirrors  have  not  been forced to close.  The FBI hasn't knocked on my door
(yet)  ;-)  And  the Streaming Media Industry is still ignoring the need for
introducing  DRM  solutions.   Most of the content is still fully accessible
using this recording tool, even the content featured on windowsmedia.com!

The Windows Media Group knows about this software, but as far as I know they
seem to ignore this "problem". In fact,  the release of this software wasn't
much of a bad thing for Microsoft, because:

-  it  makes  the ASF/WMA format more common and popular, being an "allround
   media  format"  (like  AVI, MOV or MP3).  The fact that ASF files are now
   "traded"  in file sharing systems (Scour, GNUTella, etc..) contributes to
   the  success  of  the Media Player versus its arch enemies RealPlayer and
   QuickTime.
-  Microsoft  now  has  better  arguments for establishing and selling their
   Digital  Rights  Management  solutions  which  will  clearly  give them a
   stronger position in future markets.

What  I  didn't  expect  at  all  was a tempting job offer that I got from a
company  in  the streaming media business.  No, not from Microsoft's Windows
Media  Group  ;-)  But  from one of the major players in the web hosting and
streaming services.  So in the future, I will focus on making streaming more
secure,  reliable  and  enjoyable  for both the end users and the providers,
which  also implies I will have to quit working on this project.  This means
that  there  will  never  be  any Unicast TCP or UDP support in ASFRecorder,
unless someone else decides to continue this project.



----------------------------------------------------------------------------
                           General announcements
----------------------------------------------------------------------------

This  tool is distributed freely with full source code included.  The author
wants to remain anonymous.  Source code may be used and changed as you like.
Use  this  program at your own risk.  No warranties for correct function can
be given.

This  document in some parts expresses the personal opinion of the author as
an  individual  with  the rights to speak, think and express himself freely.
Please excuse any typing errors or grammatical deficiencies in this text.

Please  spread  and  mirror this program on many sites.  From  the author's
point of view, there  is  nothing  illegal  about  this  particular program
and its distribution archive (see legal section for details).



----------------------------------------------------------------------------
                         So what is this all about?
----------------------------------------------------------------------------

This  tool enables you to download streaming content in Windows Media Format
to  your  hard  drive.  The resulting files will be in ASF format and can be
played with Windows Media Player and derived tools.

You  may  call  this  the  "DeCSS"  for Windows Media - although neither any
serious  reverse-engineering nor any particular knowledge about protcols was
necessary to program this simple application.

Development time overall:  several hours for a first, working streaming code
and   some  more  days  for  general  performance  tweaking,  cross-platform
portability,  the  Windows graphical user interface and the XML (redirection
file) parser.

For program usage:  See below



----------------------------------------------------------------------------
              The impact on the music and streaming industry?
----------------------------------------------------------------------------

Until  now, most people thought Microsoft streaming media cannot be saved or
copied...

This  program  creates  the  possibility  to DOWNLOAD LEGACY AND COPYRIGHTED
CONTENT  -  live or pre-recorded - from any Microsoft streaming media server
that  offers  HTTP streaming.  This has the potential to make some headlines
in the news (which it actually did in some publications).

Now  content  providers  will  have  to seriously reconsider their policy to
provide  high-quality, legacy content using non-encrypted, non-authenticated
and generally insecure data channels.

I  am  talking  about content providers offering music videos, recordings of
concerts  and TV  broadcasts  in  "high bandwidth" (300kbit/s and 700kbit/s)
video.  Same applies to  streaming  audio.  There is virtually no difference
to offering opyrighted MP3 files  for public download on a freely accessible
server.

HELLO CONTENT PROVIDERS!
YOUR CONTENT CAN BE AS EASILY COPIED AS IT CAN NOW BEEN DOWNLOADED FROM YOUR
SERVERS!  WOULD YOU MIND COPY-PROTECTING THIS CONTENT, PLEASE?

HELLO MUSIC INDUSTRY AND ARTISTS!
THE  CONTENT  PROVIDERS ARE CURRENTLY GIVING AWAY YOUR INTELLECTUAL PROPERTY
IN  AN  INSECURE, NON COPY-PROTECTED DATA FORMAT.  JUST LIKE MP3!  THESE ASF
FILES CAN BE DOWNLOADED AND COPIED WITHOUT ANY PHYSICAL RESTRICTION.



WHAT CAN CONTENT PROVIDERS DO ABOUT IT ?

- Disable HTTP and TCP streaming?

  Wouldn't  really  help.  UDP streaming could also be recorded by a program
  similar to this.

- Switch from Microsoft to RealMedia products?

  Not  much difference.  I am pretty sure the RealMedia servers have exactly
  the same vulnerabilities in their streaming protocols.

- Finally start using digital rights management and authentification methods
  offered by Windows Media?

  I  hope  so.  This would make an attack like this very difficult.  Windows
  Media  is  not  generally insecure.  It  does in fact offer digital rights
  management and encryption methods.  Get yourself informed.



WHAT CAN THE MUSIC INDUSTRY DO ABOUT IT ?

- Pull back from the internet business?

  Bad idea. Would give MP3 pirating a serious boost.

- Force content providers to use secure methods for providing their streams?

  I hope so.



WHAT CAN MICROSOFT DO ABOUT IT ?

- Try to find out who wrote this program and sue him?

  Bad idea - from the author's point of view.

- Inform  content  providers  and  the music industry about how to correctly
  encode  media  streams and configure servers so that the content cannot be
  downloaded and copied _that_ easily?

  Yeah, good idea.

- Implement  an effective authentification mechanism to make sure only Media
  Player and no other program can access the data streams?

  Why didn't they do it already?  It would have made this attack impossible.
  Does  it  always  require  a "LOVELETTER.vbs" or a tool like this to prove
  that some Microsoft products are unsafe/insecure (when incorrectly used)?



----------------------------------------------------------------------------
              Some advantages/special features of this utility
----------------------------------------------------------------------------

* With  this utility it is possible to download high-quality (high bandwith)
  content  using  a  low-bandwidth  connection  (e.g.   modem) for later and
  repeated replay.

* You  can  record  live video content from web cams and internet broadcasts
  that you can't record otherwise.

* The  code  is  written  in  portable ANSI-C, so it can be compiled on many
  operating  systems.   The  INTEL  byte-ordering  of  the  data  stream  is
  processed   in   a  system-independent  manner.   Only  the  GUI  code  is
  windows-specific  and is limited to a Windows platform.  Download a stream
  at university/at work on Unix systems and enjoy it at home on your PC.

* This   tool   is   using   a   HTTP   streaming   protocol.    HTTP  is  a
  connection-oriented  protocol  based on TCP.  The protocol layer has built
  in  error correction (ARQ).  So packet loss does not have any influence on
  visual  or acoustic quality of the downloaded stream.  You will always get
  the same quality that the source stream on the media server can offer.

* HTTP  streaming  passes  most  firewalls.  UDP does not.  That is the only
  reason why it was implemented by Microsoft.

* This utility supports automatic resuming of an interrupted download.

* This  utility  does  _not_  send  detailed information about your computer
  system  to the media server, as the Windows Media Player does (monitor the
  packet traffic for a  HTTP transmission and  see  yourself, if  you  don't
  believe me)



----------------------------------------------------------------------------
                 Usage as a stand-alone Windows application
----------------------------------------------------------------------------

The  Windows GUI offers a simple player interface.  It can play a variety of
media file formats.  Actually it can show any media file that your installed
DirectShow (also called ActiveMovie) drivers can play.

The buttons - from left to right - are as follows:

- Play
- Pause
- Stop
- Preview Stream
- Cancel Transfer

There  is  no volume control and no fast-forward or rewind button.  However,
you can reposition the stream using the position slider.

The  most interesting part is the "Open URL" option.  Just type the URL of a
media  file  on a Windows Media Server (it must offer HTTP streaming at this
time!) and hit the "Okay" button.

After a short time -assuming that the stream is available-  ASFRecorder will
prompt  you  for  a  file  name  to  save  the stream to.  You can select an
appropriate destination directory and file name for your stream.

ASFRecorder will remember the 25  last recently accessed URLs.  To resume an
aborted  download,  just  request the stream again and specify the very file
that contains the partial stream.  Your download will then resume. Note that
you cannot currently resume live streams. Always specify  a new file  or you
will lose your old live recording.

During  download  you will see a progress indicator in the status bar and on
the  slider.   You  may  preview  the  stream while download is in progress.
However  you  can  only  preview the stream up to the position that has been
downloaded so far (as indicated on the slider).

During downloads, you do have the possibility to replay any other media file
that resides on your hard drive.  By hitting the "preview"  button again you
can return to the stream you are currently downloading.

The program's status bar gives you the following information:

- Received kilobytes so far
- Percentage of stream so far
- current Timestamp in stream (d:h:m:s.ms)
- Data chunk sequence number
- Program status information

The program supports drag & drop,  but only one file at a time.  Drag & drop
with URLs from Internet Explorer is currently not supported yet.

You can configure a HTTP proxy server if you are situated behind a firewall.
Just use the "Proxy Server" menu item in the Settings menu.

Before  complaining  about the too simple and non-flexible player interface,
please  keep  in mind that this program is a quick hack that was finished in
about one-week by an author who started with very little Windows API and GUI
programming  knowledge.  And, besides the player functionality has only been
added for a quick preview of the streams.



----------------------------------------------------------------------------
              Usage from a Web Browser (Windows platform only)
----------------------------------------------------------------------------

The program has the ability to register as  default application for  the  so
called  "redirector  files". These files have the file extension .asx, .wax,
.wvx  and  .wmx.  Redirector files  usually contain references to the actual
stream URL.

By  registering  ASFRecorder as  a standard application for these files, the
program  will be launched every time you click on a link to any WindowsMedia
stream  in  your  web  browser and it will immediately begin to download the
stream.

The  Windows Media Player will, however, remain the standard player for your
downloaded streams (ASF, WMA, WMV).  So by clicking on these files the Media
Player  will  be  used  for replay.  That is because it offers a much better
player interface than ASFRecorder.

You may any time restore the previous  settings by unregistering ASFRecorder
as  the  standard  application for the redirector files.  Then Windows Media
Player regains full control.

At  this point, it is not possible to intercept streams that are replayed on
web  sites  that embed  the Media Player into the web page.  For downloading
these streams, you have to access the "File/Properties" menu of the embedded
Media Player to get the URL of the stream.  An alternative is to look at the
web page's source code to find out what stream URL is referenced.  For  more
details, see the section "How to find out the stream URL in Webpage-embedded
Media Players".



----------------------------------------------------------------------------
                 Usage from a shell console (all platforms)
----------------------------------------------------------------------------

asfrecorder -a <user:passwd> -P <proxy:port> -p <port> -m <recording time>
            -e <one or more stream references or URLs> -r -d -b
            
NEW IN VERSION 1.1: Command line options are case sensitive! (-p, -P)

A  <stream  reference>  is  an URL pointing to a http:// or mms:// stream in
Windows  Media  streaming  format.   The  only  streaming protocol currently
supported by this utility is HTTP streaming. Proxy servers are currently not
supported.

You  can  also  specify a <stream reference> that is an ASX, WVX, WAX or WMX
file  on  your  hard  drive.   The program will then download all the stream
references specified in  these files.  You may also use DOS wild cards (?,*)
in order to  batch-download the streams referenced  by a large number of ASX
files.

By  specifying  several  files  or  URLs,  you  can do batch downloads.  For
disabling  blocking GUI operations  like the "Save As" file dialog, you have
to use the -b option (see some paragraphs below for a detailed description).

Some examples of using ASFRecorder

asfrecorder -b mms://server.com/coolstream.asf  C:\Movie_Trailer.asx
asfrecorder -b *.asx

Valid  URLs  may  start  with  http:// or mms:// or straightforward with the
server name.  Some syntactically correct - but purely fictional - URLs are:

http://content.provider.com/any/number/of/subdirectories/streamfile.asf

mms://any.media.provider.com:80/example.asf

my.favourite.provider.com/streamfile.asf

-a  <user:passwd>  is  used  to  provide a user name and password for a user
authentification process.  So you can finally download content that you have
paid  for.   Most of you guys requesting that feature probably want porn ;-)
Note  that  this  password  is  used  on all supplied stream references.  It
cannot  be  changed  individually  for  each  reference  (like the -m and -p
option, for example)

-P  <proxy>  tells  the  program  to access a proxy server.  By specifying a
proxy  server,  you  can  access  streams  even if you are situated behind a
firewall  that  does not allow a direct HTTP connection.  The correct syntax
for  the  proxy  specification  is "http://proxy.at.my.institute:8080" where
http://  may  be  omitted.   Note  that, your institute or organization will
actually use a a different server or port number.

-p <portnum> is an optional parameter where you can specify a different port
number than 80 (which is the default port number used by HTTP). This option
does not currently work in conjunction with the -P (proxy) option.

-r  enables  creation  of  a  raw  output file.  This dumps the raw contents
received  on the HTTP connection to your hard drive.  The resulting raw file
is not a valid ASF file!  This option is probably only useful for debugging,
programming or reverse-engineering purposes.

-d  enables  dumping  the full HTTP client request and server replies to the
console.   This is for programmers and for technically interested people who
want to find out how the media server works.

-b  enables  batch  mode.  It will stop the GUI from asking for a file name.
The  stream  files  will  all  be  saved  to the current directory.  Dialogs
showing  critical  errors  will  be replaced by a message in the status bar.

-m  specifies the maximum recording time in minutes. This is useful for live
streams which you want to record unattended. By using a task scheduling tool
you can start the recording at a given time. Record network events, TV shows
and radio programs even while you are asleep or not at home.

The -p and -m parameters are defining the port/time for all following stream
references. You can change these options inbetween the stream references.

asfrecorder -m 30 tvshow.asx -m 0 mms://server/stream.asf

This will first record 30 minutes of a tv program (asx file resides on disk),
followed by a second stream without any time restriction. The 0 disables any
previously given time limit.

asfrecorder -a jeff:joshua -P proxy.domain:1234 mms://nude.com/chicks.asf

This is an example of downloading some "nude chicks" that are protected with
a  user/password  authorization using a  proxy server. Of  course  all these
parameters are purely fictional.

-e defines the following stream references as  referencing the same content,
although this  content may be available from different servers.  The purpose
of this  flag is  to download  only  one of these  references and ignore the
rest.

asfrecorder -e URL1 URL2 URL3 -e URL3 URL4

This will  download URL1  and  ignore URL2 and  URL3 if  URL1 was available.
Otherwise URL2 will be tried.  If URL2 was unavailable,  URL3 will be tried.
The second -e flag specifies another group of URLs. So URL3 will be tried in
any case, but URL4 only if URL3 was not available



----------------------------------------------------------------------------
      How to find out the stream URL in Webpage-embedded Media Players
----------------------------------------------------------------------------

Move the  mouse  over the  embedded player window and  use the  right  mouse
button to pop up the context menu of the Media Player.

Select Properties.  Click the "Show" (or "Clip") tab.  In the Location field
you  will  find  the server and directory name.  To the right of the item is
the ASX or ASF stream name.

Now merge the server and stream name to get a complete URL (like this).

mms://servername/optional/directories/streamname.asf

Enter this URL into ASFRecorder (File/Open URL...) or pass  it as  a command
line argument and here we go...

*** Alternative #1:

Click into the frame  that contains  the embedded  Media Player. Right-click
and select "View Source". Now Notepad (or similar)  will pop up.  Search for
an URL reference  that contains  either .asf or .asx.  Copy  and paste  this
into the "Open URL" dialog of ASFRecorder and here we go....

I am sure that you will find out how it will work for many other sites.  You
might also find some sites where it wont't work at all ;-)

*** Alternative #2:

Some ASX redirector files must be downloaded  because clicking on the links
does not bring up ASFRecorder even if the  redirector  file types have been
registered.  In Internet explorer,  use the right  mouse button to show the
link's context menu and select "Save Link As...". I  suggest  you save  the
ASX file to your desktop and double-click it there. Now ASFRecorder will do
its job.



----------------------------------------------------------------------------
               Questions and Answers on Program Operation (FAQ)
----------------------------------------------------------------------------


Q: Why does the audio/video preview  sometimes stop while  download is still
   in progress? Why can't I restart the replay using the play button then?
   
A: In this case, move the position slider backwards (just a little bit)  and
   press  the "Play" button again.  By moving the position slider, you force
   DirectShow to recognize the new end-of-file position.

   Technical Background:
   DirectShow  will play the incomplete  ASF  file which has been written to
   disk  so far.  Sometimes  the  "WindowsMedia source filter"  (built  into
   DirectShow)  encounters  the  end  of  that  file.  It will remember this
   end-of-file  position,  regardless  of  whether  ASFRecorder  has already
   downloaded  and appended some new data to that file.  Even  if  you press
   "Play"  again, DirectShow still thinks the end of the file is at the same
   position and won't play.
   


Q: Video and/or audio preview does not work in ASFRecorder!

A: It might be that  you  are missing  the DirectShow/ActiveMovie  transform
   filters that are required for playing WindowsMedia.

   First, try reinstalling  the full  Windows Media Player 6.4  distribution
   archive.  If this still does not help, install the  "Windows Media Tools"
   that can be obtained on the Microsoft web site. Have a look at

   http://msdn.microsoft.com/windowsmedia/
   or
   http://www.microsoft.com/windows/windowsmedia/
   (see the "Downloads" page)

   

Q: When starting the program, I only receive the message "missing DLL export
   API WSAEnumEvents", "A required DLL is missing (ws2_32.dll)" or similar.

A: You seeem to have Windows 95 OSR 1 installed.  Your  ws2_32.dll (WinSock)
   is too  old or  not existing. You need to install the latest WinSock2 DLL.
   The update archive  can be downloaded from
   
   http://www.microsoft.com/windows95/downloads/contents/wuadmintools/s_wunetworkingtools/w95sockets2/?RLD=114

   The download is  approximately 960kb in size. You  will need to reboot in
   order to complete the installation. The filename is "W95ws2setup.exe"

   In case this URL should become outdated,  try to search for "WinSock"  on
   the Microsoft web site and find the link to the Windows 95 update.



Q: My friends using Windows 98 or 2000 do get a fancy color gradient  in the
   main window, but my program window looks quite monochrome. Why that?

A: You are missing the "msimg32.dll".

   You can get this DLL from "The DLL archive" on the Internet.
   
   The URL is: http://solo.abac.com/dllarchive/M.html

   After downloading, put it either in your WINDOWS\SYSTEM directory or copy
   it into the ASFRecorder program directory. Now you  should get that fancy
   color gradient as well. Be warned: The effect may render quite slowly.



Q: I  have a fast connection to the internet!  Why does the stream arrive at
   a constant, low data rate?

A: That's  the  concept  of  streaming.  The stream is sent by the server at
   exactly the data rate that is necessary for realtime replay.  So a 56kbit
   stream  will arrive at a constant rate of 56kbit, no matter how fast your
   internet uplink is.



Q: Can downloading be accellerated?

A: Depends on the server.

   There  is a RATE specification in the HTTP header used for requesting the
   stream (see source code).  Modifying this RATE to anything different than
   1.0 makes most servers  reply with  an  error message  of "500 - internal
   server error". So you are limited to the stream's original data rate.

   However you can request and download different streams at the same time -
   until your available bandwidth is consumed.



Q: During replay, when moving the position slider, seeking within the stream
   is very slow.  What is the problem?

A: A Windows Media server does not transmit the index data of the ASF files.
   This  index  data  is  required for fast seeking in the stream.  You can,
   however generate a new index for the ASF files after download.  Therefore
   you  have  to  obtain  the Windows Media Tools from Microsoft and use the
   "ASF Indexer" to generate a new index.
   
   Windows Media Player 7.0  even  completely refuses  to seek in downloaded
   video  streams. The  position slider will  just pop back to  the position
   where it was before. I suggest you better use Windows Media Player 6.4.



Q: I have  already installed  Windows Media Player 7.0 - how can I downgrade
   to version 6.4?
   
A: You  don't have  to downgrade  because  Windows Media Player 6.4 is still
   present  on your system.  You will  find it  in the  Windows Media Player
   directory  as "mplayer2.exe".  Create a shortcut  on the desktop pointing
   to this  executable and you  can start the  Media Player 6.4 when needed.
   Using the  "Execute..." command in the start menu  with "mplayer2.exe" as
   argument works as well.



Q: I  receive the error code "connect() failed:  CONNREFUSED" or  "404 - NOT
   FOUND" for streams on some servers.  Why this?

A: Bummer.   The  server  does  not  allow  access  using the HTTP streaming
   protocol.  Besides prohibiting  access for most users  behind a firewall,
   this  does  also  prohibit access  for the  ASFRecorder  utility. Give up
   trying and download a different stream on a different server.



----------------------------------------------------------------------------
               Questions and Answers on Safety and Protocols
----------------------------------------------------------------------------


Q: Is this a "crack" of Windows Media?

A: No.   This  is  not  a  crack.   This  program  is  just  a simple client
   application  that  receives  streaming  data and stores it on hard drive.
   The  program  looks  like  a standard "Windows Media Player" to the media
   server on the other end.

   It  was  not  necessary  to break any security or encryption barriers for
   obtaining  the  raw stream data.  The protocol used for streaming is very
   simple  and  based  on HTTP - a standard protocol used for the "word wide
   web".

   And  that  is  the  scandal  about all this.  Why does the music industry
   complain  about the MP3 piracy when - at the same time - they offer equal
   content in a similar, equally unsafe manner?



Q: Is  Windows  Media  unsafe?   Why  is  it possible to simply download the
   streams?

A: This  is  not  a problem with Microsoft or Windows Media in general.  The
   Windows Media Toolkit does in fact offer possibilities for digital rights
   management and secure, authenticated and even encrypted channels.

   The  problem  is  with  the  lazyness of the content providers.  Very few
   companies actually use the available options of digital rights management
   and encryption.



Q: Will you ever implement the Unicast TCP and UDP protocols in ASFRecorder?

A: I do possess  the knowledge  to do that and  there is already a prototype
   implementation. However, I do  not intend to  use this technology  in the
   context of recording streams (now I virtually  hear a  dozen of Microsoft
   executives and developers breathing out in relief).
   
   Work on ASFRecorder has been terminated.



----------------------------------------------------------------------------
            Questions and Answers on Legal and Copyright Issues
----------------------------------------------------------------------------


Q: Does this tool infringe any Microsoft patents?

A: From my point of view: A definitive No!

   This  tool  was  developed using neither the Microsoft Format SDK nor the
   Windows  Media  Tools SDK.  The licensing conditions of these SDKs do not
   apply  here.   In  order  to  save  the ASF files to a storage medium, no
   specific  knowledge  about  the  inner  ASF  file  structure  was needed.
   Basically the data is saved in the very same format  as it arrives on the
   HTTP connection. The only thing that needs to be determined  by this tool
   is the segment (chunk) size for saving syntactically correct ASF files.

   Microsoft does claim a patent on the ASF file format in the United States
   and  possibly  in  other  countries as well.  There has been at least one
   successful  attempt to  reverse engineer the ASF format by a GNU software
   author.   The  program I am talking about is VirtualDub 1.3 by Avery Lee.
   By  threatening him with legal action, Microsoft has forced the author to
   remove  support  for  loading  ASF  media  files  because of the programs
   ability  to  transcode  these  media files to AVI format.  You can find a
   nice article about all this on the following URL:

   http://www.advogato.org/article/101.html

   But  as  I  told you, it was not really necessary to reverse-engineer the
   ASF  file format in this case.  I still know very little about the format
   itself.  The program just saves it to disk.



Q: Is it legal to use this tool?

A: That depends on what content you actually download with this tool.  If it
   is copyrighted content and if the download is expressly prohibited by the
   content provider, you are acting in an illegal manner.



Q: So is it legal to download and distribute this tool?

A: Yes. This is a very simple tool using a very simple internet protocol. It
   does  NOT break any encryption or authentification procedure.  So I don't
   see  any  point  why  this  program could be illegal.  Download, copy and
   spread as you like, THIS PROGRAM AND ITS SOURCE CODE IS LEGAL.



----------------------------------------------------------------------------
                    Bugs and limitations of this utility
----------------------------------------------------------------------------

You are welcome to fix the following (potential) problems in this program:

Problems that remain are:

* ASFRecorder cannot capture TCP/UDP-only streams (and probably never will).
  If  you  get  a  "CONNREFUSED" or "404 - NOT FOUND" message, you know that
  this stream cannot be accessed with ASFRecorder.

* ASFRecorder works for WindowsMedia only (no RealMedia, no QuickTime).

* ASFRecorder cannot handle streams with variable packet sizes (I personally
  never encountered such a stream, so they must be quite rare).

* In some cases,  ASFRecorder responds with "200 - OK", but doesn't download
  a  stream.   In this case, try to download the .ASX file with your browser
  and  open  it  with ASFRecorder (e.g.  use drag & drop or double-click the
  file  after  you  have  registered  the  ASX  file  type for ASFRecorder).
  Sometimes, manually editing the ASX file (or extracting the .asf reference
  by hand) will help.

* In the command line version, you still cannot override the output filename
  for the stream.

* The GUI still isn't very "De Luxe" and the player functionality sucks.

* Recording  of live streams  cannot currently  be  resumed. So  you  better
  specify a  different target file  for the ASF stream.  Otherwise your  old
  file will be overwritten.

* Will   probably   fail  on  copy-protected  streams that require a license
  to stream or play.

* Will  fail if the server allows TCP/UDP streaming only.  Error  message in
  this case:  connect() failed:  "CONNREFUSED" or "404 - NOT FOUND".

* Might  fail on some streams  that make  use of yet unknown extensions or a
  different header layout of the file or streaming protocol.

* Does not show plaintext strings for network errors in the console version.

* The  program  is only working properly for streams up to 4 GB in size.  It
  is  not  possible  to  allow  processing  of  larger  files without losing
  cross-platform (ANSI-C) compatiblity.

* The  GUI  only  offers  a very simple player interface.  Other players are
  much more powerful and flexible.



----------------------------------------------------------------------------
                 My personal wish list of program-features
----------------------------------------------------------------------------

The  following  features  did not make it into this program, because of time
restrictions.   I  wanted  to get a working release on the way as quickly as
possible.  You are welcome to implement these features:

* A  video  preview  area  inside  the  main window (like in Media Player or
  RealPlayer)

* A full screen mode for the video preview and a volume slider.

* Internet URL Drag & Drop support for the main window.

* Tooltips for the buttons/status bar in the main window



----------------------------------------------------------------------------
                            Program compilation
----------------------------------------------------------------------------

In the header section  of the source file "asfrecorder.c" you will find some
instructions for compilation on different platforms. The program is known to
compile on Linux, SunOS, CygWin/Windows and Visual C++.

The GUI version can only be built on the Windows platform. You do NOT need a
commercial compiler like MS Visual C++ to build this fancy little program!



----------------------------------------------------------------------------
                 How to setup the free GCC compiler on Windows
----------------------------------------------------------------------------

There are  two  basic steps  of installation for the  compiler and  required
libraries and it won't cost you a single penny!

1)

Just get the CygWin B20.1 package from Cygnus (it's free!).  It  offers Unix
functionality in Console (aka DOS) windows. You should be used to working in
Unix/Linux environments  in order to feel at home in the  CygWin bash shell.
The CygWin B20.1 package is installed using a setup utility.

I recommend to install the following packages (binary archives only)

* CygWin system and shell
cygwin-1.1.2, ash, bash
* the basic Unix shell tools
fileutils, shellutils, textutils, less, grep, gzip, tar
* tools for displaying and formatting man and info pages
man, groff, texinfo
* The compiler, linker and make utility
binutils, gcc, make

If you are familiar with Unix,  you may want to install some more, depending
on your needs and requirements.

Download  the documents archive (cygwin-docs.tar.gz)  from the Documentation
link on the CygWin home page. I suggest you read the doc "cygwin-ug-net.pdf"
file to get a quick introduction into CygWin and its basic configuration.

2)

Now get the free Win32 headers and libraries  and install these  in your lib
and include directory  (simply by  untar'ing  the archive  into the root '/'
directory)

3)

And now the easy part: Compilation!

After changing  into the  asfrecorder directory,  a single "make"  should be
sufficient to compile my baby in both the GUI and the console version.


Where to get all this fine and free software:
---------------------------------------------

*** Get CygWin B20.1 here:

http://sourceware.cygnus.com/cygwin/

On the FTP mirror sites you will find the "latest" directory. This contains
a file called SETUP.EXE - using this SETUP.EXE you can install the complete
CygWin package either  from internet  or from  the current directory (given
that you downloaded all the packages that are of interest to you)

Just have a look how many unix  tools and applications have  been ported to
the  CygWin  environment! (http://sourceware.cygnus.com/cygwin/ported.html)

*** Get the latest Win32 headers here (required for compilation!)

ftp://ftp.xraylith.wisc.edu/pub/khan/gnu-win32/cygwin/gcc-2.95.2/


Internet resources about using GCC on Windows
----------------------------------------------

For  compiling programs that are able to run without the CygWin environment,
use the -mno-cygwin compiler option.  A HOWTO text file on this topic can be
downloaded from:

http://www.xraylith.wisc.edu/~khan/software/gnu-win32/mno-cygwin-howto.txt

A very detailed FAQ about mingw is also available from:
http://www.mingw.org/mingwfaq.shtml

Colin  Peters  offers  an excellent tutorial on building Win32 programs with
GCC on his hompage (http://www.geocities.com/Tokyo/Towers/6162/win32.zip)

http://www.geocities.com/Tokyo/Towers/6162/gcc.html


Did  you know that you can even compile DirectX programs and games with GCC?
DirectX 6.1 headers/libraries for GCC are available from:

http://pws.prserv.net/thefortins/cyg-directx.html



----------------------------------------------------------------------------
                     Who is the author of this program?
----------------------------------------------------------------------------

The author is not willing to reveal his identity.

Microsoft  has  already shown that they are not willing to let anyone tamper
with  their  proprietary  ASF  media  format (see the VirtualDub issue).  It
takes an American government to win a court trial against Microsoft.

And  besides  this  source  code  is  really  not  an  example  of excellent
programming style.  So why should it be labelled with my name?

In case anyone ever claims to have programmed this original release, you can
be sure he is a liar. The author  of this program is  never going to  reveal
his identity. And that's for sure.



----------------------------------------------------------------------------
                What software was used to develop this tool?
----------------------------------------------------------------------------

- The  CygWin32  platform   (available for free from Cygnus Solutions, Inc.)

  Used as development environment.  I don't trust VisualC++,  it might leave
  behind some GUIDs and fingerprints in the EXE file.

- GNU C compiler (gcc).

  Used for compilation on Windows and on SUN platform.

- Windows  Packet  capture library and Network Analyzer 2.02  (available for
  free from the University Politecnico di Torino, Italy)

  Used for spying on network protocols and packets.

- frhed

  A  free  (non-shareware,  non-commercial)  HEX editor.  Used for getting a
  peek on streamed and locally stored ASF files.

- Windows Media Player.

  For playing and testing ASF downloaded streams.



----------------------------------------------------------------------------
                         Other recommended software
----------------------------------------------------------------------------

You  will  find  the  following software on the web using appropriate search
engines like AltaVista and FTP search.

- VirtualDub 1.3c (try "virtual dub" and "virtualdub" in the search engines)

  allows conversion of ASF files to AVI format.  This is no software that is
  easy  to use.  Important:  The current version 1.3d no longer supports the
  ASF file format. So get the 1.3c version  (not available from the author's
  web site anymore)

- Shuffler Music converter (available on www.illustrate.org)

  allows transcoding of WMA files to MP3 (might not work with copy-protected
  content, but most providers do not set the copyright bit in their streams)
  You may need to rename ASF streams to WMA for transcoding them. This  tool
  is open source as well (for Borland CPP). The  tool  can  rip  audio  data
  from combined audio/video streams, but generally takes too much  processor
  time (makes system unusable during conversion).
  
- PAM (available on http://pam.au-ja.de/, also listed on CNETs winfiles.com)

  Nice audio/video player.  Supports ASF video. Has playlist  management and
  can be "skinned" like WinAmp. It's free software. A slight disadvantage is
  the fact that it was written in VisualBasic and is sometimes slow.

- WinAmp (get it on www.winamp.com)

  for playing streaming  or downloaded WMAs and ASFs,  however this  tool is
  limited to audio. Video in ASFs will be ignored.

- DivX video codec (a hacked version of Microsofts MPEG 4 video codec).

  Records  and  plays  MPEG4  data  to/from  AVI files.  Could be useful for
  transcoding the ASF files to different formats.  Writing a transcoder does
  require  a profound programming  knowledge and further reverse-engineering
  of the ASF format.



----------------------------------------------------------------------------
               Some recommended streaming media web sites
----------------------------------------------------------------------------

There are far  more  Windows Media streaming  web sites on  the Internet, so
this list represents only a small selection:
 
www.windowsmedia.com - for  a  comprehensive  selection of streaming Windows
                       media content on the web.  Links to many other sites.

www.montreuxjazz.com - Get a recording of the world's greatest jazz festival
                       in 2000!  The highlight is a  Deep Purple gig lasting
                       two hours. Footage of two weeks of concerts  on three
                       different stages are available (up to 300 kbit/s).
                       
www.cinemapop.com    - Get  complete  movies (predominantly  movie  classics
                       like Bonanza). Has  a members  and a  guest  section.
                       Movies in the guest  section are  very old.  However,
                       by guessing the ASF references, even  non-members can
                       download the member movies (up to 300 kbit/s).

www.launch.com       - A  lot of  WindowsMedia streaming  music videos here.
                       7000 videos at up  to 300 kbit/s are accessible.  If
                       you  disable cookies in  your browser, you  can even
                       download more  than 1 trial video  without having to
                       sign up as a member.

www.centerseat.com   - offers music videos, movie  trailers  and much  more.

www.vidnet.com       - for streaming music videos  and movie trailers etc...

www.streambox.com    - a search engine and catalog for streaming media files
                       on the web. The majority  of content is  for the Real
                       Player,  but  you   can  also  find  downloadable ASF
                       streams there.

www.sonixradio.de    - pretty cool audio streams (techno mixes  from various
                       DJ's), 32kbit/sec WMA stereo. Approximately 1 hour or
                       12-16 MB per stream.

www.jamtv.tunes.com  - This site rocks! Excellent  broadband  music  videos,
                       live streams and webcast archives. Be sure  to check
                       out the "videos / broadband videos" section!.



More  web  sites  are  be recommended by fellow users on this message board:
http://pub18.ezboard.com/basfrecorder

Any user input is welcome!



----------------------------------------------------------------------------
                      Does this program have a future?
----------------------------------------------------------------------------

I do not intend to continue working on this project.  But the  sourcecode is
available  and I  hope many  programmers  will try  to improve this program.
Unfortunately, there has been  little feedback  from skilled  programmers so
far. Just some ideas and recommendations:

* Create  an ActiveX control,  that "wraps around" the  Windows Media Player
  ActiveX control  and forwards  the URL to ASFRecorder.  This allows a very
  convenient  recording  from web pages  that embed  the Media Player in the
  page.

* Please  support  this  program  on  your  home  page.   Spread, upload and
  distribute it as quickly as you can.  Please keep the distribution archive
  UNINFECTED of any viruses and backdoors.

* Can  _you_  do it with Real Networks?  Who does the first working release?
  Let's  start  a  contest!   You  will  only  have to rewrite or expand the
  networking   code.    The  GUI  already  exists  -  it  only  needs  minor
  modifications.

* Translate  this  README.TXT to your native language.  Translate the GUI to
  your native language.  I am sorry  for not using unicode  for the strings.
  Also, I did not put all the strings into the resource file. Oops.

* Add  code  for a cool Macintosh or X11 (KDE) GUI.  Now as Media Player 7.0
  beta  is available  for Mac, a  Macintosh  port of ASFRecorder is a really
  cool idea.

* Write a Media player clone or a Media player shell with a record button.

* Write a proxy server for pre-recorded streaming content.  It could be used
  at universities and network backbones to reduce network traffic a lot.

* Write a better GUI than mine and add a media mangement tool for downloaded
  content (like RealJukebox or MusicMatch Jukebox).

* Monitor  UDP  traffic and adapt this program to the UDP streaming protocol
  used  by  Microsoft.   I am pretty sure the data frame format must be very
  similar to the one used in HTTP streaming.  Recording UDP data requires to
  arrange  incoming  packets  in the right order before saving (use the seq.
  number  for  sorting).   Packet loss could be compensated by re-requesting
  any missing portions of the stream.

* Write  your  own - maybe platform independend - streaming media server for
  HTTP and/or UDP streaming Windows Media content (wow, what a nightmare for
  Microsoft),  although I don't really see a point in it.  The RTSP protocol
  is  an open, non-proprietary streaming protocol standard and probably much
  better.

* Modify  the  source  code to simultaneously request several fragments of a
  single  stream.   This  allows  faster  access to this stream, allowing to
  download at any multiple of the stream's original data rate (assuming your
  own and the content provider's internet connection offers enough bandwith)

* If  you  are  the hacker-type guy, then you might be interested in finding
  more vulnerabilities in the Windows Media format (clearing copyright bits,
  breaking authentification and encryption, hacking windows media DLLs etc)

* Write  a  transcoding tool (WMA to MP3, ASF/WMV to AVI or MPEG).  However,
  be  warned:   If  you base this work on Microsoft's Windows Media or Audio
  SDK,  you  are violating their SDK lincense conditions.  If you don't base
  your  work  on thir SDKs, you might get in conflict Microsoft's patents on
  the  ASF  file  format.   However I doubt that patents describing a simple
  file/  frame  format  are  valid  in  every  country  or could be enforced
  everywhere.



And finally...

----------------------------------------------------------------------------
  You have the permission to use my source code as a base for shareware or
commercial development (It may be up to you to fight it out with Microsoft).

                        May the source be with you.
----------------------------------------------------------------------------


                 Don't expect my name or signature here ;-)
