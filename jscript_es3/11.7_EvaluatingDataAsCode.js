const x = 1;

function evalAndReturnX(code) {
    console.log("evaluating code: " + code);
    eval(code);
    return x;
}

console.log(evalAndReturnX("var x = 2"));
console.log(x);
