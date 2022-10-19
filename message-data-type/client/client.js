const { io } = require("socket.io-client");
const socket = io('http://localhost:3000')
const readline = require('node:readline')
const { stdin: input, stdout: output } = require('node:process');

const clientInfo = {
    name: ""
}

// This is the client side code
var start = true;

const sendService = () => {
    let rl = readline.createInterface({ input, output });
    if (start === true) {
        console.log('Successfully connected to server...');
        start = false;
        rl.question(`Enter your name: `, (clientName) => {
            readline.moveCursor(process.stdout, 0, -1);
            readline.clearLine(process.stdout, 1);
            console.log(`Hello ${clientName}!`);
            clientInfo.name = clientName;
            rl.close(); 
            setTimeout(() => sendService(), 300)
        });
    }
    rl.question('> ', msg => {
        readline.moveCursor(process.stdout, 0, -1);
        readline.clearLine(process.stdout, 1);
        socket.emit('message-sent', { clientInfo, msg });
        rl.close();
        setTimeout(() => sendService(), 300);

    });
}

socket.on('message-received', (data) => {

    if (data.id != socket.id) {
        readline.moveCursor(process.stdout, 0, -1);
        readline.clearLine(process.stdout, 0);
        console.log(`${data.message.clientInfo.name}: ${data.message.msg}`);
        console.log('> ');
    } else {
        console.log(`You: ${data.message.msg}`)
    }
});

sendService();