
/** Loesung fuer Aufgabe Creature im Praktikum Softwareentwicklung I, WS 2017/18
 * @author Schmidt Felix, schmidtfelix.95@gmx.de
 * @version 07.01.2018 Kommentare und Programmkopf
 */

import java.util.Arrays;

public class Parasite extends CreatureAtribute {
    private static final int MAX_HEALTH = 3;
    private final Creature[] hosts;
    private final String name;
    
    public Parasite(Creature... hosts) {
        super(MAX_HEALTH, MAX_HEALTH);
        this.hosts = new Creature[hosts.length];
        for (int index = 0; index < hosts.length; index++) {    
            if (hosts[index] == null) {
                throw new NullPointerException();
            } else {
                this.hosts[index] = hosts[index];
            }
        }
        final StringBuilder hostNames = new StringBuilder();
        for (Creature host : hosts) {
            if (host.getName() == null) {
                hostNames.append("");
            } else {
                hostNames.append(host.getName());
            }
        }
        this.name = hostNames.toString();
    }

    private Creature[] getHosts() {
        return hosts;
    }
    
    
    private Creature getHost(int index) {
        return hosts[index];
    }
    
    @Override
    public String getName() {
        return name;
    }
    
    @Override
    public Creature hurt() {
        int index = 0;
        while (index < getHosts().length && getHost(index).getHealth() == 0) {
            ++index;
        }
        if (index == getHosts().length) {
            super.hurt();
        } else {
            getHost(index).hurt();
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
        
        final Parasite other = (Parasite) obj;
        if (!this.getName().equals(other.getName())) 
            return false;
        
        return Arrays.deepEquals(this.getHosts(), other.getHosts());
    }

    
    
    
}
