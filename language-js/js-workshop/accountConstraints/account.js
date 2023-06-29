"use strict";

const { InvalidUsernameError, InvalidPasswordError, InvalidYearOfBirthError } = require("./accountError");

class Account {
    username = "";
    password = "";
    yearOfBirth = "";

    constructor(username, password, yearOfBirth)
    {
        if (username.length == 0)
            throw new InvalidUsernameError("error: Bad username: empty username");

        let regexUsername = /^[a-zA-Z0-9-_]+$/;
        if (!regexUsername.test(username))
            throw new InvalidUsernameError("error: Bad username: wrong character");


        if (typeof yearOfBirth != 'number'  || yearOfBirth > 2022 || yearOfBirth <= 1800)
            throw new InvalidYearOfBirthError("error: Bad yearOfBirth: impossible");


        let passwordSize = password.length;
        if (passwordSize < 8 || passwordSize > 100)
            throw new InvalidPasswordError("error: Bad password: wrong size");

        let regexNumber = /.*[0-9].*/;
        let regexUppercase = /.*[A-Z].*/;
        let regexLowercase = /.*[a-z].*/;
        if(!regexNumber.test(password) || !regexUppercase.test(password) || !regexLowercase.test(password))
            throw new InvalidPasswordError("error: Bad password: needed one character of each type");

        this.username = username;
        this.password = password;
        this.yearOfBirth = yearOfBirth;
    }
}

module.exports = {
    Account
}
