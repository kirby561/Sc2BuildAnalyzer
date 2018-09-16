#pragma once

#include "Build.h"
#include <QVector>

/**
 * Contains settings for rules to use when comparing builds.
 **/
class BuildComparisonParams {
public:
	double CompareTimeS = 360;				// Number of seconds to compare in the replay.  (AKA 60 means compare the first 60 seconds).
	double CompareTimeFudgeFactorS = 5;		// Number of seconds after the CompareTimeS to allow if one build is late (If for example you have a late starport but it's the same build and it falls just outside the compare window)
};

/**
 * Contains the details of a comparison that was done between 2 builds.
 **/
class BuildComparison {
public:
	float Result = 0.0f;
};

class BuildComparator {
public:
	BuildComparator() {}

	/**
	 * Compares the 2 builds and indicates how similar they are.
	 * @param build1 The first build.
	 * @param build2 The second build.
	 * @return Returns a BuildComparison indicating how similar they are and other details about the comparison.  
	 *			This number is based off the edit distance between the 2 builds given.  A lower number indicates the builds are more similar.  
	 *			A larger number indicates they are further away.
	 **/
	BuildComparison Compare(Build build1, Build build2);

	/**
	 * Sets the parameters to use when comparing builds.  This must be set prior to calling Compare.
	 * @param params The parameters to use.
	 **/
	void SetBuildComparisonParams(BuildComparisonParams params) { _params = params; }

private:
	BuildComparisonParams _params;

	/**
	 * Trims the given build to the given amount of time.  All entries that occurred after the given time are removed.
	 * @param build The build to filter.
	 * @param timeS The last time to include in seconds.
	 * @return Returns the modified list.
	 **/
	QVector<BuildEntry> TrimBuild(const QList<BuildEntry>& build, double timeS);

	/**
	 * Returns the minimum of the 3 given numbers.
	 **/
	float BuildComparator::Min(float n1, float n2, float n3);
};
