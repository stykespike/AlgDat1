
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */
public abstract class CreatureAtribute implements Creature {
    private int health;
    private final int maxHealth;
    
    public CreatureAtribute(int health, int maxHealth) {
        this.health = health;
        this.maxHealth = maxHealth;
    }
    
    @Override
    public int getMaxHealth() {
        return maxHealth;
    }
    
    @Override
    public int getHealth() {
        return health;
    }
    
    @Override
    public Creature heal() {
        if (isAlive() && getHealth() < getMaxHealth()) {
            setHealth(getHealth()+1);
        }
        return this;
    }
    
    @Override
    public Creature hurt() {
        if (isAlive()) {
            setHealth(getHealth()-1);
        }
        return this;
    }

    private void setHealth(int health) {
        this.health = health;
    }
    
    @Override
    public String toString() {
        return "name=" + getName() + ", " + "health=" 
                + getHealth() + ", " + "alive=" + isAlive();
    }

    @Override
    public int hashCode() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) 
            return true;
        
        if (obj == null) 
            return false;
        if (getClass() != obj.getClass()) 
            return false;
        
        final CreatureAtribute other = (CreatureAtribute) obj;
        if (this.getHealth() != other.getHealth()) 
            return false;
        
        return this.getMaxHealth() == other.getMaxHealth();
    }
    
    
    
}
