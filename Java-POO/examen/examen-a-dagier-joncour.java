/**************************************************************************
 * Test final - groupe jour
 * @author: Dagier-Joncour Thomas
 *
 * ~ Travail individuel (50% de la note finale) ~
 *
 * Remarques
 * - Un oral peut valider votre note finale
 * - le nombre de points total est de 50 
 * - 5 points de pénalités au minimum sont déduits pour chaque violation d'une consigne
 *
 * Avertissement
 * - La fraude, participation ou la tentative de fraude, de même que le 
 *   plagiat peut entraîner l'échec du module et peut faire l'objet de 
 *   sanctions disciplinaires.
 *
  Consignes importantes (5 points de pénalités au minimum par contraintes)
 * 1. restez connecté sur Discord durant toute la durée du test
 * 2. indiquez votre nom suivi de votre prénom à la troisième ligne
 * 3. renommez ce fichier "examen-a-nom.java" où nom est votre nom de famille. 
 *    s'il est composé, utilisez des tirets et non des espaces.
 * 4. répondez directement sur ce document dans les blocs "à compléter"
 * 5. réalisez le maximum de commit 
 *   - environ un commit par fonctionnalité. Minimum de 5-6 commits pour les
 *     exercices les plus longs, 1-2 pour les plus courts.
 * 6. déposez ce document dans votre repo poo2020exercices/examen/examen-a-nom.java
 *   - dès que ce document est déposé, réalisé votre premier commit/push 
 *     appelé "version initiale" et vérifiez rapidement le succès de l'opération.
 *   - votre dernier commit doit s'appeler "version finale"
 * 
 * Documentation
 * 
 * Exceptions connues:
 * `IOException` (`extends Exception`), `RuntimeException`, `NullPointerException`, 
 * `IndexOutOfBoundsException`, `ClassCastException`, `ArithmeticException`, 
 * `IllegalStateException`, `NoSuchElementException`, 
 * `UnsupportedOperationException`, `TypeNotPresentException`, `EventException`
 * 
 * Signature de Lambdas/interfaces fonctionnelles connues:
 * | java.util.function | signature      | utilisation         |
 * |:-------------------|:---------------|:--------------------|
 * | `Function<T,R>`    | `T -> R`       | `R apply(T t)`      |
 * | `Consumer<T>`      | `T -> ()`      | `void accept(T t)`  |
 * | `Supplier<T>`      | `() -> T`      | `T get()`           |
 * | `Predicate<T>`     | `T -> boolean` | `boolean test(T t)` |
 * | `Runnable`         | `() -> ()`     | `void run()`        |
 * ************************************************************************/

/* ************************************************************************
 * Ex 1 - (5 pts)
 *
 * L'extrait de la classe `Article`  ci-dessous représente un article 
 * stocké dans un inventaire. Redéfinissez la méthode `equals()` 
 * uniquement, pour permettre de comparer l'égalité entre deux articles. 
 * Deux articles sont égaux s'ils ont le même id et les mêmes tags.
 * ************************************************************************/

// à compléter -------------------------------------------------------------
class Article {
  private String id;
  private int quantity;
  private double price;
  private List<Tag> tags;

  // A compléter

  @Override
    public boolean equals(Object o) {
      if(this == o) return true;
        if(o == null || o.getClass() != this.getClass()) {
          return false; 
        }
      Article other = (Article)o;
      return this.id.equals(other.id) && (this.tags.equals(other.tags));
    }
    @Override
    public int hashCode() {
      return Objects.hash(this.id, this.tags);
    }
}
// -------------------------------------------------------------------------

/* ************************************************************************
 * Ex 2 - (5 pts)
 *
 * Ecrivez l'interface fonctionnelle `Merger` permettant d'utiliser
 * la méthode `aggregate` de `Manager`. 
 *
 * La dernière ligne doit compiler !
 * ************************************************************************/

// extrait -----------------------------------------------------------------
class Manager {
  private Student a1;
  private Student a2;
  public int aggregate(Merger m) {
    return m.join(a1, a2);
  }
}
...
Manager oneManager = ...;
int total = oneManager.aggregate( (Student s1, Student s2) -> s1.age() + s2.age() );
// -------------------------------------------------------------------------

// à compléter -------------------------------------------------------------
@FunctionalInterface 
interface Merger {
  int join(Student a1, Student a2);
}
// -------------------------------------------------------------------------

/* ************************************************************************
 * Ex 3 - (20 pts)
 * 
 * Nous avons vu dans le cours deux types de containers. Les collections 
 * qui peuvent contenir **0 à n** éléments de même type et l'`Optional` 
 * qui peut contenir **0 ou 1** élément. Dans cet exercice, vous allez 
 * créer un container pouvant contenir **0 à 2** éléments de même type 
 * que nous nommerons `TwoOptions`.
 * 
 * Vous devez **impérativement** respecter les consignes suivantes:
 * 
 * - la mise en oeuvre doit se faire à l'aide de l'*enum pattern* vu en cours
 *   C'est-à-dire une interface `TwoOptions` et trois sous-classes internes 
 *   représentant les trois états.
 * - les constructeurs doivent être privés. Offrez des fabriques à la place:
 *   - construction d'un container vide: 
 *       `TwoOptions<Integer> o = TwoOptions.empty()`,
 *   - construction d'un container d'un élément: 
 *       `TwoOptions<Integer> o = TwoOptions.of(22)`,
 *   - construction d'un containter de deux éléments: 
 *       `TwoOptions<String> o = TwoOptions.of("22", "v'là les flics")`.
 * - Le type est immutable, une fois l'objet créé, il est impossible de modifier, 
 *   d'ajouter ou de supprimer les éléments
 * - Les méthodes suivantes doivent être offertes:
 *   - `isEmpty` qui précise si le container est vide
 *   - `hasOneValue` qui précise si le container contient au moins une valeur 
 *   - `hasTwoValues` qui précise si le container contient deux valeurs
 *   - `first` qui retourne la première valeur si elle existe 
 *   - `second` qui retourne la seconde valeur si elle existe 
 *   - `ifAny` qui indique si au moins un élément répond à un critère. Retourne 
 *     `false` si l'objet est vide.
 *     - par exemple: `boolean b = twoIntOpt.ifAny( i -> i >= 10 );`
 *   - appliquez la variance où cela est nécessaire.
 * - extrait d'utilisation:
 * ************************************************************************/

// extrait -----------------------------------------------------------------
TwoOptions<String> o = TwoOptions.of("22", "v'là les flics");
if (o.hasOneValue()){
  String one = o.first();
  String two = o.second();
}
if (o.ifAny( s -> s.length() > 2)){
  System.out.println("o contains at least one string with a length greater than 2");
}
// -------------------------------------------------------------------------

// à compléter -------------------------------------------------------------
interface TwoOptions<T>{

  static class EmptyOption<T> implements TwoOptions<T>{
    public EmptyOption(){

    }
    public T first(){
      throw new NoSuchElementException("nothing in this object");
    }
    public T second(){
      throw new NoSuchElementException("nothing in this object");
    }
    public boolean hasOneValue(){
      return false;
    }
    public boolean hasTwoValues(){
      return false;
    }
    public boolean ifAny(Predicate<? super T> p) {
      return false;
    }
  }

  static class OneOption<T> implements TwoOptions<T>{
    private final T elem;

    public OneOption(T t1){
      this.elem = t1;
    }
    public T first(){
      if(this.hasOneValue()){
        return elem;
      } else {
        throw new NoSuchElementException("no element in first position of object");
      }
    }
    public T second(){
      throw new NoSuchElementException("no element in second position of object");
    }
    public boolean ifAny(Predicate<? super T> p){
      return p.test(elem);
    }
    public boolean hasOneValue(){
      return true;
    }
    public boolean hasOneTwoValues(){
      return false;
    }
  }

  static class TwoOption<T> implements TwoOptions<T>{
    private final T elem1;
    private final T elem2;

    public TwoOption(T t1, T t2){
      this.elem1 = t1;
      this.elem2 = t2;
    }
    public T first(){
      if(this.hasOneValue()){
        return elem1;
      } else {
        throw new NoSuchElementException("no element in first position of object");
      }
    }
    public T second(){
      if(this.hasTwoValues()){
        return elem2;
      } else {
        throw new NoSuchElementException("no element in second position of object");
      }
    }
    public boolean ifAny(Predicate<? super T> p) {
      return p.test(elem1) || p.test(elem2);
    }
    public boolean hasOneValue(){
      return false;
    }
    public boolean hasOneTwoValues(){
      return true;
    }
  }

  public static <T> TwoOptions<T> empty(){
    return new EmptyOption<>();
  }
  public static <T> TwoOptions<T> of(T elem){
    return new OneOption<>(elem);
  }
  public static <T> TwoOptions<T> of(T elem1, T elem2){
    return new TwoOption<>(elem1, elem2);
  }
  public T first();
  public T second();
  public boolean hasOneValue();
  public boolean hasOneTwoValues();
  public boolean ifAny(Predicate<? super T> p);
}
// -------------------------------------------------------------------------


/* ************************************************************************
 * Ex 4 - (10 pts)
 *
 * Réalisez le design **minimaliste** pour que le code 
 * ci-dessous **compile**. Ne rendez publiques que les fonctionnalités 
 * visibles ci-dessous. Inutile de redéfinir les méthodes `toString`, 
 * `hashCode` ou `equals`.
 * ************************************************************************/


// extrait -----------------------------------------------------------------
Task t1 = new FileTask("/tmp/bigfile.csv");
Task t2 = new FileTask("/tmp/bigfile2.csv");
t1.whenFinished( path -> System.out.println(path + " has been treated"));
t2.whenFinished( path -> System.out.println(path + " has been treated"));
if (t1.isSuccess() && t2.isSuccess()) {
  Result res = Result.merge(t1, t2);
  res.save("/tmp/test.pdf");
}
// -------------------------------------------------------------------------


// à compléter -------------------------------------------------------------
interface Task{
  public Boolean isSuccess();
  public void whenFinished(Consumer<String> c);
}

class FileTask implements Task{
  private String path;
  private boolean success = false;

  public FileTask(String path){
    this.path = path;
  }

  public Boolean isSuccess(){
    return this.success;
  }

  public void whenFinished(Consumer<String> c){
    c.accept(this.path);
    this.success = true;
  }
}

class Result{
  public String path;
  public Task task1;
  public Task task2;

  public Result(Task a, Task b, String s){
    this.path = s;
    this.task1 = a;
    this.task2 = b;
  }

  public static Result merge(Task a, Task b){
    String s = "";
    return new Result(a, b, s);
  }
  public void save(String s){
    this.path = s;
  }
}


// -------------------------------------------------------------------------

/* ************************************************************************
 * Ex 5 - (10 pts)
 * 
 * Indiquez quelle(s) ligne(s) compile(nt) 
 *  - oui = compile/ne pose aucun problème
 *  - non = pose un problème de compilation. Dans ce cas, expliquez pourquoi
 * ************************************************************************/

// extrait -----------------------------------------------------------------
/*      Person
 *        |    
 *     Academic 
 *     /      \ 
 * Professor   Student       */
public class ClassRoom<T extends Person> {
  public ClassRoom(T t) { ... }
  public T getRandomly() { ... }
  public void add(T t) { ... }
}
...

/*[ligne 1]*/ ClassRoom<? super Academic> cr = new ClassRoom<Person>( new Student() );
/*[ligne 2]*/ Professor p = cr.getRandomly();
/*[ligne 3]*/ Academic a = cr.getRandomly();
/*[ligne 4]*/ cr.add( new Professor() );
/*[ligne 5]*/ ClassRoom<? super Person> cr = new ClassRoom<Integer>( 42 );
// -------------------------------------------------------------------------

// à compléter (ex5) -------------------------------------------------------
// remplacez les ... par votre réponse
- ligne1 [oui/non et pourquoi]
// OUI : la ligne 1 compile car un Student est une Person. De plus on fait de la contravariance et Person est bien super de Academic

- ligne2 [oui/non et pourquoi]
// NON : pas de get() en contravariance donc la ligne ne compile pas (de plus un Academic, retourné par le get() n'est pas un Professor)

- ligne3 [oui/non et pourquoi]
// NON : pas de get() en contravariance donc la ligne ne compile pas (même si un Academic est retourné dans un Academic)

- ligne4 [oui/non et pourquoi]
// OUI : la ligne 4 compile car c'est un add() donc un set() que l'on a le droit de faire en contravariance
//on ajoute un Porfessor ce qui est toléré puisque Professor hérite de Academic et la fonction add() prend un Academic en paramètre

- ligne5 [oui/non et pourquoi]
// NON : la ligne 5 ne compile pas car la class Integer n'est pas super de Person

// -------------------------------------------------------------------------