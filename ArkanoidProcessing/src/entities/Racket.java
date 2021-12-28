package entities;

import processing.core.PApplet;
import processing.core.PVector;

public class Racket extends Rect{

    private final static float height = 10;
    private final static float radiusAngle = 28;

    public Racket(PVector position, float length, PApplet processing) {
        super(position, length, height, processing);
    }

    @Override
    public void display() {
        processing.fill(120);
        processing.rect(position.x, position.y, width, height, radiusAngle);
    }

    public void getInput(float newX)
    {
        if(newX>= processing.width - width)
            newX = processing.width - width;
        position.x = newX;
    }
}
