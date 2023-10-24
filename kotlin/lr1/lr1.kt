fun main() {
    //val numbers: Array<Int> = arrayOf(1, 0, -3, 0, 2, 3, 0, -4, 5, -1, -2)
    val numbers: Array<Int> = arrayOf(5, 4, 3, 3, 2, 1, -1, -2, -2, -2, 0, 0, 0, 0);
    
    var tmp: Int
    for (i in 0..13){
        for (j in (i+1)..13){
            if ((numbers[i] > 0) and ((numbers[j] == 0) or (numbers[j] < 0))){
                tmp = numbers[i]
                numbers[i] = numbers[j]
                numbers[j] = tmp
            }
            else if ((numbers[i] == 0) and (numbers[j] < 0)){
                tmp = numbers[i]
                numbers[i] = numbers[j]
                numbers[j] = tmp
            }
        }
    }
    
    for (i in numbers){
        println(i)
    }
} 
