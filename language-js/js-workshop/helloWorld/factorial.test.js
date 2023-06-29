"use strict";

const { factorial } = require("./helloWorld");

describe("factorial", () => {

    test("factorial 0", () => {
        expect(factorial(0)).toEqual(1);
    })

    test("factorial 1", () => {
        expect(factorial(1)).toEqual(1);
    })

    test.each`
        input    | expectedResult
        ${2}     | ${2}
        ${3}     | ${6}
        ${4}     | ${24}
    `(
        "factorial $input should be equal to $expectedResult",
        ({ input, expectedResult }) => {
        expect(factorial(input)).toEqual(expectedResult);
        }
    );
})
