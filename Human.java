
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */
public class Human extends CreatureAtribute {
    private static final int MAX_HEALTH = 5;
    private final String name;
    Human(String name) {
        super(MAX_HEALTH,MAX_HEALTH);
        if (name == null) {
            throw new NullPointerException();
        }
        this.name = name;
    }
    
    @Override
    public String getName() {
        return name;
    }

    @Override
    public int hashCode() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) 
            return false;
        
        final Human other = (Human) obj;
        return this.getName().equals(other.getName());
    }
    
    
    
}
