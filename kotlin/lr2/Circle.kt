package circle

import kotlin.math.PI
import kotlin.math.abs
import kotlin.math.sqrt

class Circle (_coordinateX: Pair<Int, Int>, _coordinateY: Pair<Int, Int>) {
    var coordinateX: Pair<Int, Int> // numerator and denominator
    var coordinateY: Pair<Int, Int> // numerator and denominator
    var radius: Double
    
    init {
        coordinateX = _coordinateX
        coordinateY = _coordinateY
        radius = 0.0
    }
    
    constructor (_coordinateX: Pair<Int, Int>, _coordinateY: Pair<Int, Int>, _radius: Double) : this(_coordinateX, _coordinateY){
        radius = _radius
    }
    
    fun square() : Double {
        return PI * radius * radius
    }
    
    fun perimeter() : Double {
        return 2.0 * PI * radius
    }
    
    fun onLineWith(c1: Circle, c2: Circle) : Boolean {
        val x1 : Double = (c1.coordinateX.first / c1.coordinateX.second).toDouble()
        val y1 : Double = (c1.coordinateY.first / c1.coordinateY.second).toDouble()
        
        val x2 : Double = (c2.coordinateX.first / c2.coordinateX.second).toDouble()
        val y2 : Double = (c2.coordinateY.first / c2.coordinateY.second).toDouble()
        
        val x3 : Double = (this.coordinateX.first / this.coordinateX.second).toDouble()
        val y3 : Double = (this.coordinateY.first / this.coordinateY.second).toDouble()
        
        val a : Double = y2 - y1
        val b : Double = x1 - x2
        val c : Double = x1 * (y1 - y2) + y1 * (x2 - x1)
        
        val d : Double = abs(a * x3 + b * y3 + c) / sqrt(a * a + b * b)
        
        return (d <= 1e-10)
    }
    
    operator fun plus(c: Circle): Circle {
        return Circle(coordinateX, coordinateY, radius + c.radius)
    }
}

fun maxCircle(circles: ArrayList<Circle>) : Int{
    if (circles.size == 0)
        return -1
    
    var maxR: Double = circles[0].radius
    var maxID: Int = 0
    for (c in circles.indices){
        if (maxR < circles[c].radius){
            maxR = circles[c].radius
            maxID = c
        }
    }
    
    return maxID
}

fun minCircle(circles: ArrayList<Circle>) : Int{
    if (circles.size == 0)
        return -1
    
    var minR: Double = circles[0].radius
    var minID: Int = 0
    for (c in circles.indices){
        if (minR > circles[c].radius){
            minR = circles[c].radius
            minID = c
        }
    }
    
    return minID
}

fun groupCirclesByLine(circles : ArrayList<Circle>) : MutableSet<List<Int>> {
    var group : MutableSet<List<Int>> = mutableSetOf()
    
    for (i in circles.indices) {
        for (j in circles.indices){
            if (i != j){
                var arr: ArrayList<Int> = arrayListOf(i, j)
                for (k in circles.indices){
                    if ((k != i) and (k != j) and circles[k].onLineWith(circles[i], circles[j])){
                        arr.add(k)
                    }
                }
                group.add(arr.sorted())
            }
        }
    }
    
    return group
}
 
 
 
 
