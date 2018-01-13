
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */
public class Oger extends CreatureAtribute {
    private static final int MAX_HEALTH = 10;
    private static final int HEALTH = 5;
    private static final String NAME = "Oger";
    public Oger(){
        super(HEALTH, MAX_HEALTH);
    }

    @Override
    public String getName() {
        return NAME;
    }
    
    @Override
    public Creature attack(Creature victim) {
        if (isAlive() && !getName().equals(victim.getName())) {
            while (victim.getHealth() > 1) {
                victim.hurt();
            }
        }
        return this;
    }
    
    @Override
    public int hashCode() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) 
            return false;
        
        final Oger other = (Oger)obj;
        return getName().equals(other.getName());
    }
    
}
