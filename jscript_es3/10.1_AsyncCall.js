function resolveAfter2Seconds() {
    return new Promise(resolve => {
	console.log('new Promise');
	setTimeout(() => { resolve('resolved'); }, 2000);
    });
}

async function asyncCall() {
    console.log('calling');
    var result = await resolveAfter2Seconds();
    console.log('result');
}

asyncCall();
