
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */
public class Fairy extends CreatureAtribute {
    private static final int MAX_HEALTH = 4;
    private boolean vulnerable = true;
    private final String name;
    
    public Fairy(String name) {
        super(MAX_HEALTH, MAX_HEALTH);
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
    public Creature heal() {
        for (int count = 0; count < 2; count++) {
            super.heal();
        }
        return this;
    }
    
    @Override
    public Creature hurt() {
        if (isVulnerable()) {
            super.hurt();
        }
        setVulnerable(!isVulnerable());
        return this;
    }
    
    private boolean isVulnerable() {
        return vulnerable;
    }
    
    private void setVulnerable(boolean status) {
        this.vulnerable = status;
    }

    @Override
    public int hashCode() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) 
            return false;
        
        final Fairy other = (Fairy) obj;
        if (this.isVulnerable() != other.isVulnerable()) 
            return false;
        
        return this.getName().equals(other.getName());
    }
    
    
    
}
