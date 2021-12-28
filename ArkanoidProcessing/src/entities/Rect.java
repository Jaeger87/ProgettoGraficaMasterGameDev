package entities;

import processing.core.PApplet;
import processing.core.PVector;

public abstract class Rect extends Entity {

    protected float width;
    protected float height;


    public Rect(PVector position, float width, float height, PApplet processing) {
        super(position, processing);
        this.width = width;
        this.height = height;
    }
}
