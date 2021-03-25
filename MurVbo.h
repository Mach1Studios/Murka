#pragma once

#if defined(MURKA_OF)

#include "MurkaTypes.h"

class MurVbo {
    vector<MurkaPoint> verts;
    vector<MurkaPoint> texCoords;
    int usage = 0;

public:
    ofVbo internal;

    MurVbo(){}

	bool isInited() {
		return internal.getIsAllocated();
	}

	void setup() {
	}
	
	void setVertexData(MurkaPoint* _verts, int total) {
        this->verts.resize(total);
        memcpy(this->verts.data(), _verts, total * sizeof(MurkaPoint));
	}

    void setTexCoordData(MurkaPoint* texCoords, int total) {
        this->texCoords.resize(total);
        memcpy(this->texCoords.data(), texCoords, total * sizeof(MurkaPoint));
    }
    
    void update(int usage) {
		this->usage = usage;
		internal.setVertexData(&this->verts[0].x, 2, this->verts.size(), this->usage, sizeof(MurkaPoint));
        internal.setTexCoordData(&this->texCoords[0].x, this->texCoords.size(), this->usage, sizeof(MurkaPoint));
    }
    
    void clear() {
        internal.clear();
    }
};

#elif defined(MURKA_JUCE)

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_opengl/juce_opengl.h"

#include "MurkaTypes.h"


class MurVbo {
	struct UVCoord {
		float u;
		float v;
	};

	struct VertexCoord {
		float x;
		float y;
		float z;
	};

	vector<MurkaPoint> verts;
    vector<MurkaPoint> texCoords;

	struct VboData {
		VertexCoord vert;
		UVCoord texCoord;
	};

	vector<VboData> vboData;

	GLuint VAO = 0, VBO = 0;
	OpenGLContext* openGLContext = nullptr;

public:
	MurVbo() {

	}

	~MurVbo() {
		if (isInited()) clear();
	}

	bool isInited() {
		return VAO && VBO;
	}

	void setOpenGLContext(OpenGLContext* openGLContext) {
		this->openGLContext = openGLContext;
	}

	void setup() {
		openGLContext->extensions.glGenVertexArrays(1, &VAO);
		openGLContext->extensions.glGenBuffers(1, &VBO);
	}

	void clear() {
		openGLContext->extensions.glDeleteVertexArrays(1, &VAO);
		openGLContext->extensions.glDeleteBuffers(1, &VBO);

		VAO = 0;
		VBO = 0;
	}

	void setVertexData(const MurkaPoint* _verts, int total) {
        this->verts.resize(total);
        memcpy(this->verts.data(), _verts, total * sizeof(MurkaPoint));
	}

    void setTexCoordData(const MurkaPoint* texCoords, int total) {
        this->texCoords.resize(total);
        memcpy(this->texCoords.data(), texCoords, total * sizeof(MurkaPoint));
	}

    void update(int usage = GL_STATIC_DRAW) {
		int size = (std::max)(verts.size(), texCoords.size());

		vboData.resize(size);
		for (int i = 0; i < verts.size(); i++) {
			vboData[i].vert.x = verts[i].x;
			vboData[i].vert.y = verts[i].y;
			vboData[i].vert.z = 0;
		}
		 
		for (int i = 0; i < texCoords.size(); i++) {
			vboData[i].texCoord.u = texCoords[i].x;
			vboData[i].texCoord.v = texCoords[i].y;
		}
		 

		openGLContext->extensions.glBindVertexArray(VAO);
		openGLContext->extensions.glBindBuffer(GL_ARRAY_BUFFER, VBO);
		openGLContext->extensions.glBufferData(GL_ARRAY_BUFFER, size * sizeof(VboData), vboData.data(), usage);

		openGLContext->extensions.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VboData), (GLvoid*)offsetof(VboData, vert));
		openGLContext->extensions.glEnableVertexAttribArray(0);

		openGLContext->extensions.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VboData), (GLvoid*)offsetof(VboData, texCoord));
		openGLContext->extensions.glEnableVertexAttribArray(1);

		openGLContext->extensions.glBindBuffer(GL_ARRAY_BUFFER, 0);
		openGLContext->extensions.glBindVertexArray(0);
	}

	void internalDraw(GLuint drawMode, int first, int total) const {
		openGLContext->extensions.glBindVertexArray(VAO);
		glDrawArrays(drawMode, first, total); 
		openGLContext->extensions.glBindVertexArray(0);
	}
    
};

#else // Default version

class MurVbo {
public:
    MurVbo(){};
};

#endif
