package entities;

import processing.core.PApplet;
import processing.core.PVector;

import java.util.List;

public class Sphere extends Entity{

    private PVector velocity;
    private final static float radius = 11;
    private final static float SQUARERADIUS = 11 ^ 2;
    private boolean alive = true;
    private boolean cooldown = false;


    public Sphere(PVector position, PApplet processing) {
        super(position, processing);
        velocity = new PVector(2,-2);
    }

    @Override
    public void display() {
        processing.fill(0,230,0);
        processing.ellipse(position.x,position.y, radius, radius);
    }

    public void update(Racket racket, List<Brick> bricks)
    {
        position.add(velocity);

        // CheckWalls
        if(position.x - radius <= 0 || position.x + radius >= processing.width)
        {
            cooldown = false;
            velocity.x *= -1;
        }

        if(position.y - radius <= 0)
        {
            cooldown = false;
            velocity.y *= -1;
        }

        if(velocity.y + radius >= processing.height)
            alive = false;

        if(!cooldown && checkRectCollision(racket))
        {
            cooldown = true;
        }

        for (Brick b: bricks) {
            if(b.isAlive() && checkRectCollision(b))
            {
                b.hit();
                cooldown = false;
            }

        }

    }

    private enum RECTCOLLISIONTYPE {LENGTH, WIDTH};

    private boolean checkRectCollision(Rect rect) {

        PVector leftTop = new PVector(rect.position.x, rect.position.y);
        PVector rightTop = new PVector(rect.position.x + rect.width, rect.position.y);
        PVector leftBottom = new PVector(rect.position.x, rect.position.y + rect.height);
        PVector rightBottom = new PVector(rect.position.x + rect.width, rect.position.y + rect.height);

        boolean bottomCollision;
        boolean topCollision = false;
        boolean leftCollision;
        boolean rightCollision = false;



        bottomCollision = lineCircle(leftBottom, rightBottom, RECTCOLLISIONTYPE.WIDTH);
        if(!bottomCollision)
            topCollision = lineCircle(leftTop, rightTop, RECTCOLLISIONTYPE.WIDTH);

        if(topCollision || bottomCollision)
            velocity.y *= -1;

        leftCollision = lineCircle(leftTop, leftBottom, RECTCOLLISIONTYPE.LENGTH);
        if(!leftCollision)
            rightCollision = lineCircle(rightTop, rightBottom, RECTCOLLISIONTYPE.LENGTH);

        if(leftCollision || rightCollision)
            velocity.x *= -1;

        return topCollision || bottomCollision || leftCollision || rightCollision;
    }

    private boolean lineCircle(PVector point1, PVector point2, RECTCOLLISIONTYPE type) {

        // is either end INSIDE the circle?
        // if so, return true immediately
        boolean inside1 = pointCircle(point1);
        boolean inside2 = pointCircle(point2);
        if (inside1 || inside2) return true;

        // get length of the line
        float len = type == RECTCOLLISIONTYPE.WIDTH ? Math.abs(point1.x - point2.x) :
                Math.abs(point1.y - point2.y);

        // get dot product of the line and circle
        float dot = ( ((position.x-point1.x)*(point2.x-point1.x)) +
                ((position.y-point1.y)*(point2.y-point1.y)) ) / PApplet.pow(len,2);

        // find the closest point on the line
        float closestX = point1.x + (dot * (point2.x-point1.x));
        float closestY = point1.y + (dot * (point2.y-point1.y));

        PVector closestPoint = new PVector(closestX, closestY);
        // is this point actually on the line segment?
        // if so keep going, but if not, return false
        boolean onSegment = linePoint(point1, point2, len, closestPoint);
        if (!onSegment) return false;

        // get distance to closest point
        float distX = closestX - position.x;
        float distY = closestY - position.y;
        float squareDistance = (distX*distX) + (distY*distY);

        if (squareDistance <= SQUARERADIUS) {
            return true;
        }
        return false;
    }


    // POINT/CIRCLE
    private boolean pointCircle(PVector point) {

        // get distance between the point and circle's center
        // using the Pythagorean Theorem
        float distX = point.x - position.x;
        float distY = point.y - position.y;
        float squareDistance =  (distX*distX) + (distY*distY);

        // if the distance is less than the circle's
        // radius the point is inside!
        if (squareDistance <= SQUARERADIUS) {
            return true;
        }
        return false;
    }


    // LINE/POINT
    private boolean linePoint(PVector point1, PVector point2, float lineLen, PVector pointX) {

        // get distance from the point to the two ends of the line
        float d1 = pointX.dist(point1);
        float d2 = pointX.dist(point2);

        // since floats are so minutely accurate, add
        // a little buffer zone that will give collision
        float buffer = 0.1f;    // higher # = less accurate

        // if the two distances are equal to the line's
        // length, the point is on the line!
        // note we use the buffer here to give a range,
        // rather than one #
        if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
            return true;
        }
        return false;
    }

}
