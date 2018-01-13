
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */

public class Zombie extends CreatureAtribute {
    private static final int MAX_HEALTH = 0;
    private String name;
    
    public Zombie() {
        super(MAX_HEALTH, MAX_HEALTH);
    }

    @Override
    public String getName() {
        return name;
    }
    
    private void setName(String name) {
        this.name = name;
    }
    
    @Override
    public Creature attack(Creature victim) {
        if (victim == null) {
            setName(null);
        } else {
            setName(victim.getName());
            victim.hurt().hurt();
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
        
        final Zombie other = (Zombie) obj;
        return this.getName().equals(other.getName());
    }
    
    
    
}
