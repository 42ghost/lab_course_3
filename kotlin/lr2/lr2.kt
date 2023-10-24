import circle.*

fun main() {
    /*var circles : ArrayList<Circle> = arrayListOf()
    circles.add(Circle(Pair(1, 1), Pair(1, 1), 2.0))
    circles.add(Circle(Pair(2, 1), Pair(2, 1), 1.0))
    circles.add(Circle(Pair(-1, 1), Pair(1, 1), 3.0))
    circles.add(Circle(Pair(-2, 1), Pair(1, 1), 5.0))
    circles.add(Circle(Pair(3, 1), Pair(3, 1), 4.0))
    
    println("Maximum circle numbered ${maxCircle(circles)}")
    println("Minimum circle numbered ${minCircle(circles)}")
    
    val group : MutableSet<List<Int>> = groupCirclesByLine(circles)
    println("Groups:")
    for (g in group){
        println(g)
    }*/
    
    var c1 : Circle = Circle(Pair(1, 1), Pair(1, 1), 2.0)
    var c2 : Circle = Circle(Pair(2, 1), Pair(2, 1), 1.0)
    var c3 : Circle = c1 + c2
    
    println("CoordinatesX : ${c3.coordinateX.first}/${c3.coordinateX.second}")
    println("CoordinatesY : ${c3.coordinateY.first}/${c3.coordinateY.second}")
    println("Radius : ${c3.radius}")
}


