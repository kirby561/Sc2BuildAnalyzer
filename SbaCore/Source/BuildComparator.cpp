#include "BuildComparator.h"
#include <algorithm>

// ?? Untested
BuildComparison BuildComparator::Compare(Build* build1, Build* build2) {
	const QList<BuildEntry*>& build1Order = build1->GetOrder();
	const QList<BuildEntry*>& build2Order = build2->GetOrder();

	// First thing is to trim each build by the compare time
	QVector<BuildEntry*> build1Trimmed = TrimBuild(build1Order, _params.CompareTimeS);
	QVector<BuildEntry*> build2Trimmed = TrimBuild(build2Order, _params.CompareTimeS);

	// ?? TODO: Encorporate the fudge factor here

	// We'll use a dynamic programming edit distance algorithm to find the
	//    distance between the 2 builds
	int width = build1Trimmed.size() + 1;
	int height = build2Trimmed.size() + 1;
	float* distances = new float[width * height];
	for (int i = 0; i <= build1Trimmed.size(); i++) {
		for (int j = 0; j <= build2Trimmed.size(); j++) {
			if (i == 0) {
				distances[i + j * width] = j;
			} else if (j == 0) {
				distances[i + j * width] = i;
			} else if (build1Trimmed.at(i - 1)->Unit->GetUnitId() == build2Trimmed.at(j - 1)->Unit->GetUnitId()) {
				distances[i + j * width] = distances[(i - 1) + width * (j - 1)];
			} else {
				distances[i + j * width] = 1.0f + Min(distances[i + width * (j - 1)], distances[(i - 1) + width * j], distances[(i - 1) + width * (j - 1)]);
			}
		}
	}

	BuildComparison comparison;
	comparison.Result = distances[build1Trimmed.size() + width * build2Trimmed.size()];

	return comparison;
}

QVector<BuildEntry*> BuildComparator::TrimBuild(const QList<BuildEntry*>& build, double timeS) {
	QVector<BuildEntry*> result;
	
	for (int i = 0; i < build.size(); i++) {
		if (build[i]->TimestampSecs <= timeS) {
			result.append(build[i]);
		} else {
			break;
		}
	}

	return result;
}

float BuildComparator::Min(float n1, float n2, float n3) {
	return std::min(n1, std::min(n2, n3));
}
