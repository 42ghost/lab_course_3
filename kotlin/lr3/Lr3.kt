import kotlinx.coroutines.*

suspend fun countLowerLetters(str: String) : Int{
    var counter: Int = 0;
    for (i in str.chars()){
        if ((97 <= i) and (i <= 122)){
            counter += 1;
        }
    }
    return counter;
}

fun main(){
    println("Start main");
    var str: String = "Hello, World!";
	GlobalScope.launch {
	    delay(1000L);
        println(countLowerLetters(str))
	}
    println("End main");
    Thread.sleep(2000L)
}
