var fs = require('fs');
var SerialPort = require('serialport').SerialPort;
var argv = require('minimist')(process.argv.slice(2));

if( !argv.f || !argv.s ) {
	console.log("\n\nusage: node app -f [FILE] -s [SERIAL DEVICE]\n\n");
	process.exit(1);
}

var serialPort = new SerialPort(argv.s, { baudrate:9600 });

serialPort.on("error", function(error){
	console.error(error);
	process.exit(1);
});


serialPort.on("open", function() {
	console.log("serial port open, opening file...\n");
	
	fs.readFile(argv.f, 'binary', (err, fileData) => {
		if (err) {
			console.error("could not open file " + argv.f);
			process.exit(1);
		}
		
		var position = 0;

		serialPort.on('data', function(serialData) {
			//console.log("received data from serial: " + serialData);
			if( serialData == "o" ) {
				console.log(">> ok");
				if( position === fileData.length ) {
					console.log("done.");
					process.exit(0);
				}
				sendByte(fileData[position]);
				position++;
			}
			else {
				console.error(">> " + serialData);
				process.exit(1);
			}
		});
	});
});


var sendByte = function(data) {
	console.log("<< " + data);
	var buffer = new Buffer(data);
	serialPort.write(buffer, (error, bytesWritten) => {
		if( error ) {
			console.error("error writing " + data + ": " + error);
			process.exit(1);
		}
	});
}

