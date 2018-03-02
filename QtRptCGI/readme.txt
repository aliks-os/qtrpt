QtRptCGI

There is a possible to use a QtRPT to get reports from the Web as a pdf file.
This example show how to use it. The compiled QtRptCGI must be placed to the
folder CGI-BIN on your server. The folder CGI-BIN folder must be with rights
for execution and writing for the web-users. During execution, the generates
temporaly  the pdf file. This pdf file returns from console to QtRptCGI.
After that, the temporaly pdf file deletes from the folder.

The QtRptCGI supprorts two arguments in the command line:
argv 1 - file name of the xml file
argv 2 - sql query string if data takes from DB

To call a QtRptCGI I use the following address in browser
http://192.168.0.1/cgi-bin/test.cgi

The test.cgi conteins the following:

#!/usr/bin/perl
print "Content-type: application/pdf\n\n";
print system('./QtRptCGI file.xml');


This example was tested in eviroment:
Debian 7.0
Apache 2
Qt 4.8.2