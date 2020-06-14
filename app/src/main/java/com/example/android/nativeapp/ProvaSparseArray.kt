package com.example.android.nativeapp

import android.util.SparseArray
import objectexplorer.ObjectGraphMeasurer
import java.io.ByteArrayOutputStream
import java.io.IOException
import java.io.ObjectOutputStream
import java.io.Serializable
import java.util.*
import kotlin.collections.LinkedHashMap
import kotlin.math.pow




/*
risultati dimensione oggetti:
tag	obj	ref	length	class	size_serial
Test	1	2	0	Test	170
Hashtable	2051	6662	1024	Hashtable	15672
HashMap	2051	7175	1024	HashMap	15670
LinkedHashMap	2052	9230	1024	LinkedHashMap	15723
mutableMapOf	2052	9230	1024	LinkedHashMap	15723
MySparseArray	4	2050	1024	MySparseArray	0
SparseArray	4	2050	1024	SparseArray	0
mutableListOf	3	1238	1024	ArrayList	5339
Vector	3	1284	1024	Vector	5694
ArrayList	3	1238	1024	ArrayList	5339
LinkedList	1026	4101	1024	LinkedList	5329
array	2	1026	1024	Test[]	5375

*/


class ProvaSparseArray internal constructor() {
    companion object {
        private val TAG = ProvaSparseArray::class.java.simpleName
        private val nativeManager = NativeManager()
        @Throws(IOException::class)
        fun sizeOf(obj: Any?): Int {
            if (obj == null) return 0
            if (obj is Serializable) {
                val byteArrayOutputStream = ByteArrayOutputStream()
                val objectOutputStream = ObjectOutputStream(byteArrayOutputStream)
                objectOutputStream.writeObject(obj)
                objectOutputStream.flush()
                objectOutputStream.close()
                val byteArray = byteArrayOutputStream.toByteArray()
                return byteArray.size
            }
            else{
                return -1
            }
        }

        private fun log(key : String, length : Int, obj : Any?){
            val measure = ObjectGraphMeasurer.measure(obj)
            //measure.
            Log.v(TAG, "%s\t%s\t%s\t%s\t%s\t%s\t%s", key, measure.objects, measure.references, length, obj?.javaClass?.simpleName, sizeOf(obj), nativeManager.getSize(obj))
        }
    }

    private val list: MutableMap<String,Any> =  mutableMapOf()
    init {
        Thread {
            Log.v(TAG, "tag\tobj\tref\tlength\tclass\tsize_serial\tsize_native")
            val test = Test(10.0, true, "1",null, 10, 10, 10.0F)
            test.test = test
            log("Test", 0, test)
            val structureCompose: Array<Array<Test?>?> = arrayOfNulls(5)
            for (power in structureCompose.indices) {
                structureCompose[power] = arrayOfNulls(2.0.pow((power+10).toDouble()).toInt())
                for (index in structureCompose[power]?.indices!!) {
                    structureCompose[power]?.set(index, test)
                }
            }

            for (power in structureCompose.indices) {
                test(structureCompose[power]!!)
            }

        }.start()
    }

    private fun test(structure: Array<Test?>){
        if(true){
            val map: MutableMap<Int, Test?> = Hashtable()
            list["Hashtable"] = map
            for (index in structure.indices) {
                map[index] = structure[index]
            }
        }
        if(true){
            val map: MutableMap<Int, Test?> = HashMap()
            list["HashMap"] = map
            for (index in structure.indices) {
                map[index] = structure[index]
            }
        }
        if(true){
            val map: MutableMap<Int, Test?> = LinkedHashMap()
            list["LinkedHashMap"] = map
            for (index in structure.indices) {
                map[index] = structure[index]
            }
        }
        if(true){
            val map: MutableMap<Int, Test?> = mutableMapOf()
            list["mutableMapOf"] = map
            for (index in structure.indices) {
                map[index] = structure[index]
            }
        }
        if(true){
            val map: MutableMap<Int, Test?> = MySparseArray<Test>()
            list["MySparseArray"] = map
            for (index in structure.indices) {
                map[index] = structure[index]
            }
        }
        if(true){
            val map = SparseArray<Test?>()
            list["SparseArray"] = map
            for (index in structure.indices) {
                map.put(index, structure[index])
            }
        }
        if(true){
            val map: MutableList<Test?> = mutableListOf()
            list["mutableListOf"] = map
            for (index in structure.indices) {
                map.add(structure[index])
            }
        }
        if(true){
            val map: MutableList<Test?> = Vector()
            list["Vector"] = map
            for (index in structure.indices) {
                map.add(structure[index])
            }
        }
        if(true){
            val map: MutableList<Test?> = ArrayList()
            list["ArrayList"] = map
            for (index in structure.indices) {
                map.add(structure[index])
            }
        }
        if(true){
            val map: MutableList<Test?> = LinkedList()
            list["LinkedList"] = map
            for (index in structure.indices) {
                map.add(structure[index])
            }
        }
        for (key in list.keys) {
            val map = list[key]
            val size = ObjectGraphMeasurer.measure(map)//sizeOf(map)

            var length = 0
            if (map is SparseArray<*>){
                length = map.size()
            }
            if (map is MutableMap<*,*>){
                length = map.size
            }
            if (map is MutableList<*>){
                length = map.size
            }

            log(key, length, map)
        }
        // https://github.com/DimitrisAndreou/memory-measurer
        log("array", structure.size, structure)

    }


    class Test(double: Double, boolean: Boolean, string: String, var test : Test?, long: Long, int: Int, float: Float) : Serializable, Cloneable
}