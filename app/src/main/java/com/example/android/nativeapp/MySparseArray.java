package com.example.android.nativeapp;

import android.util.SparseArray;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;


public class MySparseArray<T> extends SparseArray<T> implements Map<Integer,T> {

    @Override
    public boolean isEmpty() {
        return super.size() == 0;
    }

    @Override
    public boolean containsKey(@Nullable final Object o) {
        return this.get(o) != null;
    }

    @Override
    public boolean containsValue(@Nullable final Object o) {
        return false;
    }

    @Nullable
    @Override
    public T get(@Nullable final Object o) {
        Object[][] obj = new Object[10][];
        if (o instanceof Integer){
            return super.get((Integer)o);
        }
        else{
            return null;
        }
    }

    @Nullable
    @Override
    public T put(@NonNull final Integer integer, @Nullable final T t) {
        super.put(integer, t);
        return t;
    }

    @Nullable
    @Override
    public T remove(@Nullable Object o) {
        if (o instanceof Integer){
            final T t = this.get(o);
            super.remove((Integer)o);
            return t;
        }
        else{
            return null;
        }
    }

    @Override
    public void putAll(@NonNull final Map<? extends Integer, ? extends T> map) {
        for(int key : map.keySet()){
            super.put(key, map.get(key));
        }
    }

    @NonNull
    @Override
    public Set<Integer> keySet() {
        final Set<Integer> result = new HashSet<>();
        for(int index = 0; index < super.size(); index++){
            result.add(super.keyAt(index));
        }
        return result;
    }

    @NonNull
    @Override
    public Collection<T> values() {
        final Collection<T> result = new ArrayList<>();
        for(int index = 0; index < super.size(); index++){
            result.add(super.valueAt(index));
        }
        return result;
    }

    @NonNull
    @Override
    public Set<Entry<Integer, T>> entrySet() {
        final Set<Entry<Integer, T>> result = new HashSet<>();
        for(int index = 0; index < super.size(); index++){
            result.add(new AbstractMap.SimpleEntry<>(super.keyAt(index),super.valueAt(index)));
        }
        return result;
    }
}
