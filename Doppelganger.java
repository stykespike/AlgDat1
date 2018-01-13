
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */
public class Doppelganger implements Creature {
    
    private final Creature mirroredOne;
    
    public Doppelganger(Creature copiedOne) {
        if (copiedOne == null) {
            throw new NullPointerException();
        }
        this.mirroredOne = copiedOne;
    }
    
    private Creature getMirroredOne() {
        return mirroredOne;
    }
    
    @Override
    public String getName() {
        return getMirroredOne().getName();
    }

    @Override
    public int getMaxHealth() {
        return getMirroredOne().getMaxHealth();
    }

    @Override
    public int getHealth() {
        return getMirroredOne().getHealth();
    }

    @Override
    public Creature heal() {
        return getMirroredOne().heal();
    }

    @Override
    public Creature hurt() {
        return getMirroredOne().hurt();
    }
    
    @Override
    public boolean isAlive() {
        return getMirroredOne().isAlive();
    }
    
    @Override
    public Creature attack(Creature victim) {
        if (this != victim) {
            getMirroredOne().attack(victim);
        }
        return this;
    }

    @Override
    public int hashCode() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean equals(Object obj) {
        return getMirroredOne().equals(obj);
    }
    
}
