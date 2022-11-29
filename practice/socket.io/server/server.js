// const express = require('express');
// const app = express();
// const http = require('http');
// const server = http.createServer(app);
const { Server } = require("socket.io");
const PORT = 3000;
const io = new Server(PORT);


io.on('connection', (socket) => {
    console.log('client connected: ', socket.id);
    
    socket.on('message-sent', (data) => {
        console.log(data);
        socket.broadcast.emit('message-received', {id:socket.id, message: data});
        // io.emit('message-received', {id: socket.id, message: data});
    });
    
})