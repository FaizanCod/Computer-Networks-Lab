var WebSocketClient = require('websocket').client;

var client = new WebSocketClient();

client.on('connect', function(connection) {
    console.log('WebSocket Client Connected');
    
    connection.on('message', function(message) {
        console.log('Message from Server : ' + message.utf8Data);
    });

    connection.send("Hello");
});

client.connect('ws://localhost:3000/', 'echo-protocol');
