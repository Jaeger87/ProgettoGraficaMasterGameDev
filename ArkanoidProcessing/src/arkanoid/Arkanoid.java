package arkanoid;

import entities.Brick;
import entities.Racket;
import entities.Sphere;
import processing.core.PApplet;
import processing.core.PVector;

import java.util.ArrayList;

public class Arkanoid extends PApplet {

    ArrayList<Brick> bricks;
    Sphere sphere;
    Racket racket;

    float startBricks = 50;
    float paddingBrikcs = 5;

    public void settings(){
        size(500, 500);
        sphere = new Sphere(new PVector(400, 350), this);
        racket = new Racket(new PVector(width / 2, height * 0.88f), width/10, this);
        bricks = new ArrayList<>();


        println(color(100,230,90));

        for(int i = 0; i < 10; i++)
            bricks.add(new Brick(new PVector(startBricks + i * Brick.BWIDTH + paddingBrikcs, 70), Brick.LIFEBRICK.HALF, this));
    }

    public void draw(){
        background(255);
        racket.getInput(mouseX);
        racket.display();

        for (Brick b: bricks) {
            b.display();
        }

        sphere.update(racket, bricks);
        sphere.display();


    }

    public static void main(String... args){
        PApplet.main("arkanoid.Arkanoid");
    }
}
