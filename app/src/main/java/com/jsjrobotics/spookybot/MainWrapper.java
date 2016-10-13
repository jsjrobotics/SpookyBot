package com.jsjrobotics.spookybot;


import com.jsjrobotics.defaultTemplate.lifecycle.wrappers.ActivityWrapper;
import com.jsjrobotics.defaultTemplate.lifecycle.wrappers.interfaces.ILifecycleActivity;

public class MainWrapper extends ActivityWrapper {
    private Main mActivity = new Main();

    @Override
    protected ILifecycleActivity getLifecycleActivity() {
        return mActivity;
    }
}
