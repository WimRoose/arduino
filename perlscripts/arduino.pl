#!/usr/bin/perl
use warnings;
use strict;

my $test;
my $moist_val;
my $update_rrd;
my $light_val;

open(MYOUTFILE, ">", "/home/lou/arduino.log") || die "Couldn't open file file.txt, $!";
# Set up the serial port
    use Device::SerialPort;
    my $port = Device::SerialPort->new("/dev/ttyACM0");
     
    # 19200, 81N on the USB ftdi driver
    $port->baudrate(9600); # you may change this value
    $port->databits(8); # but not this and the two following
    $port->parity("none");
    $port->stopbits(1);
    $port->read_const_time(2000);
    $port->read_char_time(2000);
    $port->are_match("\n");

my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;
$year += 1900;
$mon += 1;
my $datetime = sprintf "%04d%02d%02d%02d%02d%02d", $year, $mon, $mday, $hour, $min, $sec;
print "$datetime\n";

use POSIX;


my $loop=1;

# heel belangrijk: bij het printen in de loop steeds een newline toevoegen achteraan
# anders blijft het gebufferd

while ($loop == 1) {
open(MYOUTFILE, "+>>", "/home/lou/arduino.log") || die "Couldn't open file file.txt, $!";
#	$userinput =  <STDIN>;
#	chomp ($userinput);
#	my $count_out = $port->write($userinput);
#	sleep(1);
    # Poll to see if any data is coming in
   my $char = $port->lookfor(22);
	
	if ($char) {

		#my $datetime2 = strftime( '%Y%m%d%H%M%S', localtime );

		#print $datetime2 . " - " . $char . "\n";

		#print MYOUTFILE $datetime2 . " - " . $char . "\n";


		if (index($char,"m") != -1)	 {
			
			$moist_val = substr($char,19,21);
			#print "\nmoistvalue is ". $moist_val . "\n";
			$moist_val = int($moist_val);
			$update_rrd = `rrdtool update /var/www/rrd/moisture.rrd N:$moist_val;`;
			#print $moist_val."\n";
		}
		if (index($char,"l") != -1)      {

                        $light_val = substr($char,19,21);
                        #print "\nlightvalue is ". $light_val . "\n";
                        $light_val = int($light_val);
                        $update_rrd = `rrdtool update /var/www/rrd/light.rrd N:$light_val;`;
                        #print $light_val."\n";
                }
	}  
close(MYOUTFILE);

}
