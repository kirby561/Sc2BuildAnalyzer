#pragma once

/**
 * A generic listener for tracking progress of things that run in the background
 */
class ProgressListener {
public:
	virtual void OnProgressChanged(int progress, int max) = 0;
	virtual void OnFinished(int result) = 0;
};
