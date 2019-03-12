// This is generally ugly. CALLBACK HELL is the correct term.

// add two numbers remotely by calling an API

let resultA, resultB, resultC;

function addAsync(num1,num2,callback) {
    return $.getJSON('http://www.example.com', {num1: num1, num2: num2},callback);
}

addAsync(1,2,success => {
    
    // callback 1

    resultA = success;  // you get result = 3 here

    addAsync(resultA, 3, success => {

	// callback 2

	resultB = success;

	addAsync( resultB, 4, success => {

	    // callback 3

	    resultC = success; // you get result = 10 here finally

	    console.log('total' + resultC);
	    console.log(resultA, resultB, resultC);
	});
    });
});


    
