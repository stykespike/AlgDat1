
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */

public class Robot extends CreatureAtribute {
    private static final int MAX_HEALTH = 6;
    private static final int MAX_HITS = 5;
    private int hits;
    private final String name;
    
    public Robot(int serialNumber) {
        super(MAX_HEALTH, MAX_HEALTH);
        final StringBuilder serialName = new StringBuilder();
        serialName.append("Robot-").append(serialNumber);
        this.name = serialName.toString();
    }

    @Override
    public String getName() {
        return name;
    }

    private int getHits() {
        return hits;
    }

    private void setHits(int hits) {
        this.hits = hits;
    }
    
    
    
    @Override
    public Creature hurt() {
        if (getHits() < MAX_HITS) {
            setHits(getHits()+1);
        } else {
            while (isAlive()) {
                super.hurt();
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
        
        final Robot other = (Robot) obj;
        if (this.getHits() != other.getHits()) 
            return false;
        
        return this.getName().equals(other.getName());
    }
    
}
