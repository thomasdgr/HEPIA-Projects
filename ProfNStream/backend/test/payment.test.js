const assert = require('assert');

const payment = require('../modules/payment')

describe('Compute credits to debit - Test', () => {
    it('should return 1', () => {
           assert.equal(payment.computeCreditsToDebit(0,1,2), 1);
       });
    it('should return 1', () => {
        assert.equal(payment.computeCreditsToDebit(0,3,3), 1);
    });
    it('should return -1', () => {
        assert.equal(payment.computeCreditsToDebit(0,7,3), -1);
    });
    it('should return -1', () => {
        assert.equal(payment.computeCreditsToDebit(0,2,7), -1);
    });
    it('should return -1', () => {
        assert.equal(payment.computeCreditsToDebit(0,7,7), -1);
    });
    it('should return -1', () => {
        assert.equal(payment.computeCreditsToDebit(0,undefined,7), -1);
    });
    it('should return -1', () => {
        assert.equal(payment.computeCreditsToDebit(0,1,undefined), -1);
    });
   });

describe('Compute credits to debit - Test', () => {
    it('should be undefined', () => {
        assert.equal(payment.debitUser(1,2), undefined);
    });
    it('should fail', () => {
        assert.equal(payment.debitUser(7,3), "invalid idUser or amountOfCredits <= 0");
    });
    it('should fail', () => {
        assert.equal(payment.debitUser(2,-1), "invalid idUser or amountOfCredits <= 0");
    });
    it('should fail', () => {
        assert.equal(payment.debitUser(undefined,7), "idUser or amountOfCredits is undefined");
    });
    it('should fail', () => {
        assert.equal(payment.debitUser(1,undefined), "idUser or amountOfCredits is undefined");
    });
    it('should pass', () => {
        assert.equal(payment.debitUser(1,3), undefined);
    });
});

describe('Get credits from the idUser', () => {
    it('should be undefined', () => {
        assert.equal(payment.getUserCredits(undefined), "idUser is undefined");
    });
    it('should fail', () => {
        assert.equal(payment.getUserCredits(-1), "invalid idUser");
    });
    it('should return 2', () => {
        assert.equal(payment.getUserCredits(1), undefined);
    });
});