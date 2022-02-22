@FunctionalInterface
public interface TriConsumer{
    void accept(Account src, Account dst, double amount);
}