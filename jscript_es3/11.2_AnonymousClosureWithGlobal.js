let global = 'Hello, I am a global variable :)';

(function() {
    // We keep these variables private inside this closure scope

    let myGrades = [93,95,88,0,55,91];

    let average = function() {
	let total = myGrades.reduce(function(accumulator,item) {return accumulator + item},0);
	return 'Your average grade is ' + total / myGrades.length + '.';
    }

    let failing = function() {
	var failingGrades = myGrades.filter(function(item) {return item < 70;});

	return 'You failed ' + failingGrades.length + ' times.';
    }

    console.log(failing());
    console.log(global);
}());
