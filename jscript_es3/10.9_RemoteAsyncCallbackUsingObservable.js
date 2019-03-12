// add two numbers remotely using observable

let resultA, resultB, resultC;

function addAsync(num1,num2) {

    // ES6 fetch API, which returns a promise

    return fetch(`http:\/\/www.example.com?num1=${num1}&num2=${num2}`).then(x => x.json());
}

addAsync(1,2).then(success => {resultA = success; return resultA})
    .then(success => addAsync(success,3))
    .then(success => {resultB = success; return resultB;})
    .then(success => addAsync(success,4))
    .then(success => {resultC = success; return resultC;})
    .then(success => {
	console.log("total: " + success)
	console.log(resultA,resultB,resultC)
    });


		 
		 
