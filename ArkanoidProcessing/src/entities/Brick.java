package entities;

import processing.core.PApplet;
import processing.core.PVector;

public class Brick extends Rect{

    public final static float BWIDTH = 20;
    public final static float BHEIGHT = 10;
    private static int colorFullLife = 23400;
    private static int colorHalfLife = -10164646;
    private LIFEBRICK life;

    public enum LIFEBRICK {FULL, HALF, DEAD};

    public Brick(PVector position, LIFEBRICK life, PApplet processing) {

        super(position, BWIDTH, BHEIGHT, processing);
        this.life = life;
    }


    @Override
    public void display() {
        switch (life)
        {
            case FULL:
                processing.fill(colorFullLife);
                break;
            case HALF:
                processing.fill(colorHalfLife);
                break;
            case DEAD:
                return;
        }

        processing.rect(position.x, position.y, BWIDTH, BHEIGHT);
    }

    public boolean isAlive()
    {
        return life != LIFEBRICK.DEAD;
    }

    public void hit()
    {
        if(life == LIFEBRICK.FULL)
            life = LIFEBRICK.HALF;
        else
            life = LIFEBRICK.DEAD;

    }

    @Override
    public String toString() {
        return "Brick{" +
                "position=" + position +
                '}';
    }
}
