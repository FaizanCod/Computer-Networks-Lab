const { Server } = require("socket.io");
const PORT = 3000

const io = new Server(PORT);

io.on('connection', client => {
    console.log('client connected', client.id);
    client.on('message-sent', data => {
        console.log(client.id, ": ", data);
        io.emit('message-received', {id: client.id, message: data})
    });
    client.on('disconnect', () => {
        console.log('Client disconnected');
    });
});