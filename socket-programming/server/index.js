const WebSocket = require('ws');
const server = new WebSocket.Server({port : '3000'})

server.on('connection', socket => {

    console.log("Server is running on port 3000");

    socket.on('message', message => {
        console.log(`Message from Client : ${message}`)
    })

    socket.send("How you doin'?");

    socket.on('close', () => {
        console.log('Client has disconnected');
    })
})