#!/usr/bin/perl -w

use IO::Socket;
use Device::SerialPort;

# Set up the serial port
    
    my $port = Device::SerialPort->new("/dev/ttyACM0");
     
    # 19200, 81N on the USB ftdi driver
    $port->baudrate(9600); # you may change this value
    $port->databits(8); # but not this and the two following
    $port->parity("none");
    $port->stopbits(1);
    $port->read_const_time(2000);
    $port->read_char_time(2000);
#   $port->are_match("\n");


    my $sock = new IO::Socket::INET ( 

	LocalHost => '127.0.0.1', 
	LocalPort => '7070',
	Proto => 'tcp',
	Listen => 1, 
	Reuse => 1, 8 ); 
	die "Could not create socket: $!\n" unless $sock;

$i=0;
while($i == 0) {
	
	my $new_sock = $sock->accept();
	while (<$new_sock>) {

		$buf = $_;
		if ($buf =~ /^quit/)	{
			print "Closing connection...\n";
			close($sock);
			$i=1;
		}

#		my $count_out = $port->write("zetKoffie");
#		sleep(2);
#	 	# Poll to see if any data is coming in
#		if ($char) {
#			print "arduino says -> " . $char . "\n";
#		}
 	

}



}
close($sock);

