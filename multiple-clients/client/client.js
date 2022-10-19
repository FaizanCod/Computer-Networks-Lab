const { io } = require("socket.io-client");
const socket = io('http://localhost:3000')
const readline = require('node:readline')
const { stdin: input, stdout: output } = require('node:process');

const clientInfo = {
    name: "Faizan"
}

// This is the client side code

const sendService = () => {
let rl = readline.createInterface({ input, output });

    rl.question('', msg => {
        socket.emit('message-sent', { clientInfo, msg });
        rl.close();
        setTimeout(() => sendService(), 300)

    });
}

socket.on('message-received', (data) => {

    if (data.id != socket.id) {
        console.log(`${data.message.clientInfo.name}: ${data.message.msg}`)
    } else {
        console.log(`You: ${data.message.msg}`)
    }
    

})


sendService()