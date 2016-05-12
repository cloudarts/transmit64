var fs = require('fs');
var SerialPort = require('serialport').SerialPort;
var argv = require('minimist')(process.argv.slice(2));

if( !argv.f || !argv.s ) {
	console.log("\n\nusage: node app -f [FILE] -s [SERIAL DEVICE]\n\n");
	process.exit(1);
}

console.log("DON'T start the C64 client yet! Wait for Arduino warmup...");

var serialPort = new SerialPort(argv.s, { baudrate:9600 });

serialPort.on("error", function(error){
	console.error(error);
	process.exit(1);
});

// the C64 client may not be running while the Arduino is starting up.
// it will receiver false data during warmup
// so, the first write will be delayed until user confirmation that the client has been started
var firstWrite = true;

serialPort.on("open", function() {
	console.log("serial port open, opening file...\n");
	
	fs.readFile(argv.f, 'binary', (err, fileData) => {
		if (err) {
			console.error("could not open file " + argv.f);
			process.exit(1);
		}
		
		var position = 0;

		serialPort.on('data', function(serialData) {
			console.log("received data from serial: " + serialData);
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
	var delay = 0;
	if( firstWrite ) {
		delay = 5000;
		firstWrite = false;
		console.log("start C64 client NOW...");
	}

	setTimeout(function() {
		console.log("<< " + data);
		var buffer = new Buffer(data);
		if( buffer.length == 2) {
			buffer = buffer.slice(1);
		}
		serialPort.write(buffer, (error, bytesWritten) => {
			if( error ) {
				console.error("error writing " + data + ": " + error);
				process.exit(1);
			}
			console.log("<< " + parseInt(data, 10));
		});
	}, delay);
}

