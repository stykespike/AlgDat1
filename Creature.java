
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */
public interface Creature {
    String getName();
    
    int getMaxHealth();
    
    int getHealth();
    
    Creature heal();
    
    Creature hurt();
    
    default boolean isAlive() {
        return getHealth() > 0;
    }
    
    default Creature attack(Creature victim) {
        if (victim == null) {
            throw new NullPointerException();
        }
        if (isAlive() && this != victim) {
            victim.hurt();
        }
        return this;
    }
}
