package entities;

import processing.core.PApplet;
import processing.core.PVector;

public abstract class Entity {

    protected PVector position;
    protected PApplet processing;

    public Entity(PVector position, PApplet processing) {
        this.position = position;
        this.processing = processing;
    }

    public abstract void display();
}
