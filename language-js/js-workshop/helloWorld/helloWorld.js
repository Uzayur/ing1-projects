function helloWorld()
{
    console.log("Hello World!");
}

function factorial(n)
{
    let p = 1;
    let count = 1;

    while (count <= n) {
        p *= count;
        count++;
    }

    return p;
}

module.exports = {
helloWorld,
factorial,
}
