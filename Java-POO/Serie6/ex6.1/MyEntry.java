public class MyEntry {
    private Account account;
    private String errorMsg;

    public MyEntry(Account account, String errorMsg) {
        this.account = account;
        this.errorMsg = errorMsg;
    }

    public Account account() {
        return this.account;
    }

    public String errorMsg() {
        return this.errorMsg;
    }
}
