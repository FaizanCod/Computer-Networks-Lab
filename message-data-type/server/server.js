const { Server } = require("socket.io");
const PORT = 3000

const io = new Server(PORT);

io.on('connection', client => {
    console.log('client connected', client.id);
    client.on('message-sent', data => {
        var numeric = 0, alphabet = 0, special = 0, float = 0;
        const len = data.msg.length;
        for (let i=0; i<len; i++) {
            let ascii = data.msg.charCodeAt(i);
            if (ascii <= 122 && ascii >= 65)
                alphabet = 1;
            else if (ascii <= 57 && ascii >= 48)
                numeric = 1;
            else if (i+1 < len && i-1 >= 0) {
                let prev = data.msg.charCodeAt(i-1);
                let next = data.msg.charCodeAt(i+1);
                if (data.msg[i] === '.' && (prev <= 57 && prev >= 48) && (next <= 57 && next >= 48))
                    float = 1;
            }
            else
                special = 1;
        }
        if (float === 1)
            numeric == 0;
        // console.log(client.id, ": ", data);
        console.log();
        console.log(`Message from ${data.clientInfo.name}: ${data.msg}`);
        if (alphabet === 1 && special === 0 && numeric === 0 && float === 0) 
            console.log(`Message contains alphabets only.`);
        else if (alphabet === 1 && numeric === 1 && special == 0 && float === 0)
            console.log(`Message contains alphanumeric data.`);
        else if (special === 1 && numeric === 0 && alphabet === 0 && float === 0)
            console.log(`Message contains special characters only.`);
        else if (numeric === 1 && alphabet === 0 && special === 0 && float === 0)
            console.log(`Message contains numeric data only.`);
        else if (float === 1 && alphabet === 0 && special === 0)
            console.log(`Message contains floating point number.`);
        else
            console.log(`Message contains mixed data.`);
        io.emit('message-received', {id: client.id, message: data});
    });
    client.on('disconnect', () => {
        console.log('Client disconnected');
    });
});
