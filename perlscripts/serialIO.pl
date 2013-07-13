#!/usr/bin/perl
use warnings;
use strict;

my $test;
my $moist_val;
my $update_rrd;
my $light_val;
my $arduinosays;
my $port = "/dev/ttyACM" . $ARGV[0];

#open(MYOUTFILE, ">", "/home/lou/arduino.log") || die "Couldn't open file file.txt, $!";
# Set up the serial port
    use Device::SerialPort;
    my $port = Device::SerialPort->new($port);
     
    # 19200, 81N on the USB ftdi driver
    $port->baudrate(9600); # you may change this value
    $port->databits(8); # but not this and the two following
    $port->parity("none");
    $port->stopbits(1);
    $port->read_const_time(2000);
    $port->read_char_time(2000);
    #$port->are_match("\n");

#my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;
#$year += 1900;
#$mon += 1;
#my $datetime = sprintf "%04d%02d%02d%02d%02d%02d", $year, $mon, $mday, $hour, $min, $sec;
#print "$datetime\n";

use POSIX;


# heel belangrijk: bij het printen in de loop steeds een newline toevoegen achteraan
# anders blijft het gebufferd

while (1) {

	my $lees_commando = `cat /home/lou/commando`;
	my $clear_commando;

	if ($lees_commando ne "\n")	{
		chomp($lees_commando);
		print "Received from Commando: " . $lees_commando . ", sending to arduino...\n";		
		my $count_out = $port->write($lees_commando."\n");
		
		$clear_commando = `echo "" > /home/lou/commando`;
	}
#sleep(2);
	$arduinosays = $port->lookfor();

if ($arduinosays ne "")	{
print "Arduino Says: ";		
print $arduinosays. "\n";
}
#$port->lookclear();
sleep 1;
#close(MYOUTFILE);

}
