module.exports =  {computeCreditsToDebit, debitUser, getUserCredits, updatePayment, checkPayment, isUserProf, updateBannedUsers, checkUserBanned}

/**
 * Compute the number of credits to debit from the user account
 * @param {string} timestamp the amount of time the user has spent on the stream
 * @param {int} idUser the id of the user
 * @param {int} idStream the id of the stream 
 * @return {int} the number of credits or -1 as an exception occured
 */
function computeCreditsToDebit(timestamp, idUser, idStream){
    if(timestamp === undefined || idUser === undefined || idStream === undefined) {
        return;
    }
    if(idUserIsValid(idUser) && idStreamIsValid(idStream)) {
        // or any other method to compute the number of credits to debit 
        // it can depends on the watch-time, the topic (identified with the "idStream")...
        return 1; 
    } else {
        return;
    }
}

/**
 * Return a boolean as the id given exists in the database
 * @param {int} idUser the id of the user
 * @return {boolean}
 */
function idUserIsValid(idUser){
    // as the database is not created yet, we check if the idUser exists with an array
    return filterArray(userList, 'idUser', idUser).length > 0 || filterArray(streamList, 'idUser', idUser).length > 0;
}


/**
 * Return a boolean as the id given exists in the database
 * @param {int} idStream the id of the stream 
 * @return {boolean}
 */
function idStreamIsValid(idStream){
    // as the database is not created yet, we check if the idStream exists with an array
    return filterArray(streamList, 'idStream', idStream).length > 0;
}

/**
 * Return a boolean as the user has been debited correctly
 * @param {int} idUser the id of the user to debit
 * @param {int} amountOfCredits the amount of credits to debit 
 * @return {String} the status of the call
 */
function debitUser(idUser, amountOfCredits){
    if(idUser === undefined || amountOfCredits === undefined) {
        return -1;
    }
    if(idUserIsValid(idUser) && amountOfCredits > 0) {
        filterArray(userList, 'idUser', idUser)[0].credits -= amountOfCredits;
        return 0;
    } else {
        return 1;
    }
}

/**
 * Return the number of credits depeding on the idUser
 * @param {int} idUser the id of the user to debit
 * @return {int}
 */
 function getUserCredits(idUser){
    if(idUser === undefined) {
        return "idUser is undefined";
    }
    if(idUserIsValid(idUser)) {
        return filterArray(userList, 'idUser', idUser)[0].credits;
    } else {
        return "invalid idUser";
    }
}

/**
 * Update the DB as we want to know if a user paid for a specific stream at any time
 * @param {int} idUser the id of the user to debit
 * @param {int} idStream the id of the stream
 * @return {void}
 */
function updatePayment(idUser, idStream){
    if(idUserIsValid(idUser) && idStreamIsValid(idStream)){
        paymentStream.push({
            userID: idUser, streamID: idStream
        });
    }
    console.log(paymentStream);
}

/**
 * Given a userID and a streamID, check if the user has paid for the stream
 * @param {int} idUser the id of the user
 * @param {int} idStream the id of the stream
 * @return {boolean} true if he aleready paid, else false
 */
function checkPayment(idUser, idStream){
    if(idUserIsValid(idUser) && idStreamIsValid(idStream)){
        if(filterArray(paymentStream, 'userID', idUser)[0] !== undefined && 
        filterArray(paymentStream, 'streamID', idStream)[0] !== undefined){
            return true;
        }
    }
    return false;
}

/**
 * Given a userID, check if the user is a streamer or a viewer
 * @param {int} userID the name of the user
 * @return {boolean} true if he is a streamer, else false
 */function isUserProf(userID){
    return filterArray(streamList, 'idUser', userID)[0] !== undefined;
}

/**
 * Update the DB as we want to know if a user has been banned of a specific stream at any time
 * @param {int} idUser the id of the user to debit
 * @param {int} idStream the id of the stream
 * @return {void}
 */
 function updateBannedUsers(idUser, idStream){
    if(idUserIsValid(idUser) && idStreamIsValid(idStream)){
        userBanned.push({
            userID: idUser, streamID: idStream
        });
    }
    console.log(paymentStream);
}

/**
 * Given a userID and a streamID, check if the user has been banned of the stream
 * @param {int} idUser the id of the user
 * @param {int} idStream the id of the stream
 * @return {boolean} true if he aleready paid, else false
 */
function checkUserBanned(idUser, idStream){
    if(idUserIsValid(idUser) && idStreamIsValid(idStream)){
        if(filterArray(userBanned, 'userID', idUser)[0] !== undefined && 
        filterArray(userBanned, 'streamID', idStream)[0] !== undefined){
            return true;
        }
    }
}

/**
 * Return the array matching the params
 * @param {Array} array the array of users
 * @param {String} fields the field to filter
 * @param {String} value the value to use as a filter
 * @return {Array} the result of the filter
 */
 function filterArray(array, fields, value){
    fields = Array.isArray(fields) ? fields : [fields];    
    return array.filter((item) => fields.some((field) => item[field] === value));
};

// /!\ Temporary arrays used to fake database
const userList = [
    {idUser: 0, name:"thomas", credits: 10},
    {idUser: 1, name:"dorian", credits: 5},
    {idUser: 2, name:"alexey", credits: 3},
    {idUser: 3, name:"antoine", credits: 2},
    {idUser: 4, name:"gustavo", credits: 1},
    {idUser: 5, name:"trung", credits: 0},
    {idUser: 10, name:"testman", credits: 14}
];

const streamList = [
    {idStream: 0, idUser: 11, name:"orestis"},
    {idStream: 1, idUser: 12, name:"stephane"},
    {idStream: 2, idUser: 13, name:"yassin"},
    {idStream: 3, idUser: 14, name:"nabil"},
    {idStream: 4, idUser: 15, name:"paul"},
    {idStream: 5, idUser: 16, name:"adrient"}    
];

var paymentStream = []

var userBanned = [];