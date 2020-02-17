char colors[6][16] = {
    "green.png", "blue.png", "white.png", "yellow.png", "orange.png", "red.png"
};

char texName[6][16] = {
    "texture0", "texture1", "texture2", "texture3", "texture4", "texture5"
};

//set up vertex data (and buffer(s)) and configure vertex attributes
float vertices[6][3][3][6][5] = {
//green
{
    //first line
    {
        {
            0, 2, 0, 0, 0,
            1, 2, 0, 1, 0,
            0, 3, 0, 0, 1,
            1, 3, 0, 1, 1,
            1, 2, 0, 1, 0,
            0, 3, 0, 0, 1,
        },
        {
            1, 2, 0, 0, 0,
            2, 2, 0, 1, 0,
            1, 3, 0, 0, 1,
            2, 3, 0, 1, 1,
            2, 2, 0, 1, 0,
            1, 3, 0, 0, 1,
        },
        {
            2, 2, 0, 0, 0,
            3, 2, 0, 1, 0,
            2, 3, 0, 0, 1,
            3, 3, 0, 1, 1,
            3, 2, 0, 1, 0,
            2, 3, 0, 0, 1,
        },
    },
    //second line
    {
        {
            0, 1, 0, 0, 0,
            1, 1, 0, 1, 0,
            0, 2, 0, 0, 1,
            1, 2, 0, 1, 1,
            1, 1, 0, 1, 0,
            0, 2, 0, 0, 1,
        },
        {
            1, 1, 0, 0, 0,
            2, 1, 0, 1, 0,
            1, 2, 0, 0, 1,
            2, 2, 0, 1, 1,
            2, 1, 0, 1, 0,
            1, 2, 0, 0, 1,
        },
        {
            2, 1, 0, 0, 0,
            3, 1, 0, 1, 0,
            2, 2, 0, 0, 1,
            3, 2, 0, 1, 1,
            3, 1, 0, 1, 0,
            2, 2, 0, 0, 1,
        },
    },
    //third line
    {
        {
            0, 0, 0, 0, 0,
            1, 0, 0, 1, 0,
            0, 1, 0, 0, 1,
            1, 1, 0, 1, 1,
            1, 0, 0, 1, 0,
            0, 1, 0, 0, 1,
        },
        {
            1, 0, 0, 0, 0,
            2, 0, 0, 1, 0,
            1, 1, 0, 0, 1,
            2, 1, 0, 1, 1,
            2, 0, 0, 1, 0,
            1, 1, 0, 0, 1,
        },
        {
            2, 0, 0, 0, 0,
            3, 0, 0, 1, 0,
            2, 1, 0, 0, 1,
            3, 1, 0, 1, 1,
            3, 0, 0, 1, 0,
            2, 1, 0, 0, 1,
        },
    },
},

//blue
{
    //first line
    {
        {
            0, 2, 3, 0, 0,
            1, 2, 3, 1, 0,
            0, 3, 3, 0, 1,
            1, 3, 3, 1, 1,
            1, 2, 3, 1, 0,
            0, 3, 3, 0, 1,
        },
        {
            1, 2, 3, 0, 0,
            2, 2, 3, 1, 0,
            1, 3, 3, 0, 1,
            2, 3, 3, 1, 1,
            2, 2, 3, 1, 0,
            1, 3, 3, 0, 1,
        },
        {
            2, 2, 3, 0, 0,
            3, 2, 3, 1, 0,
            2, 3, 3, 0, 1,
            3, 3, 3, 1, 1,
            3, 2, 3, 1, 0,
            2, 3, 3, 0, 1,
        },
    },
    //second line
    {
        {
            0, 1, 3, 0, 0,
            1, 1, 3, 1, 0,
            0, 2, 3, 0, 1,
            1, 2, 3, 1, 1,
            1, 1, 3, 1, 0,
            0, 2, 3, 0, 1,
        },
        {
            1, 1, 3, 0, 0,
            2, 1, 3, 1, 0,
            1, 2, 3, 0, 1,
            2, 2, 3, 1, 1,
            2, 1, 3, 1, 0,
            1, 2, 3, 0, 1,
        },
        {
            2, 1, 3, 0, 0,
            3, 1, 3, 1, 0,
            2, 2, 3, 0, 1,
            3, 2, 3, 1, 1,
            3, 1, 3, 1, 0,
            2, 2, 3, 0, 1,
        },
    },
    //third line
    {
        {
            0, 0, 3, 0, 0,
            1, 0, 3, 1, 0,
            0, 1, 3, 0, 1,
            1, 1, 3, 1, 1,
            1, 0, 3, 1, 0,
            0, 1, 3, 0, 1,
        },
        {
            1, 0, 3, 0, 0,
            2, 0, 3, 1, 0,
            1, 1, 3, 0, 1,
            2, 1, 3, 1, 1,
            2, 0, 3, 1, 0,
            1, 1, 3, 0, 1,
        },
        {
            2, 0, 3, 0, 0,
            3, 0, 3, 1, 0,
            2, 1, 3, 0, 1,
            3, 1, 3, 1, 1,
            3, 0, 3, 1, 0,
            2, 1, 3, 0, 1,
        },
    },
},

//white
{
    //first line
    {
        {
            0, 0, 0, 0, 0,
            1, 0, 0, 1, 0,
            0, 0, 1, 0, 1,
            1, 0, 1, 1, 1,
            1, 0, 0, 1, 0,
            0, 0, 1, 0, 1,
        },
        {
            1, 0, 0, 0, 0,
            2, 0, 0, 1, 0,
            1, 0, 1, 0, 1,
            2, 0, 1, 1, 1,
            2, 0, 0, 1, 0,
            1, 0, 1, 0, 1,
        },
        {
            2, 0, 0, 0, 0,
            3, 0, 0, 1, 0,
            2, 0, 1, 0, 1,
            3, 0, 1, 1, 1,
            3, 0, 0, 1, 0,
            2, 0, 1, 0, 1,
        },
    },
    //second line
    {
        {
            0, 0, 1, 0, 0,
            1, 0, 1, 1, 0,
            0, 0, 2, 0, 1,
            1, 0, 2, 1, 1,
            1, 0, 1, 1, 0,
            0, 0, 2, 0, 1,
        },
        {
            1, 0, 1, 0, 0,
            2, 0, 1, 1, 0,
            1, 0, 2, 0, 1,
            2, 0, 2, 1, 1,
            2, 0, 1, 1, 0,
            1, 0, 2, 0, 1,
        },
        {
            2, 0, 1, 0, 0,
            3, 0, 1, 1, 0,
            2, 0, 2, 0, 1,
            3, 0, 2, 1, 1,
            3, 0, 1, 1, 0,
            2, 0, 2, 0, 1,
        },
    },
    //third line
    {
        {
            0, 0, 2, 0, 0,
            1, 0, 2, 1, 0,
            0, 0, 3, 0, 1,
            1, 0, 3, 1, 1,
            1, 0, 2, 1, 0,
            0, 0, 3, 0, 1,
        },
        {
            1, 0, 2, 0, 0,
            2, 0, 2, 1, 0,
            1, 0, 3, 0, 1,
            2, 0, 3, 1, 1,
            2, 0, 2, 1, 0,
            1, 0, 3, 0, 1,
        },
        {
            2, 0, 2, 0, 0,
            3, 0, 2, 1, 0,
            2, 0, 3, 0, 1,
            3, 0, 3, 1, 1,
            3, 0, 2, 1, 0,
            2, 0, 3, 0, 1,
        },
    },
},

//yellow
{
    //first line
    {
        {
            0, 3, 0, 0, 0,
            1, 3, 0, 1, 0,
            0, 3, 1, 0, 1,
            1, 3, 1, 1, 1,
            1, 3, 0, 1, 0,
            0, 3, 1, 0, 1,
        },
        {
            1, 3, 0, 0, 0,
            2, 3, 0, 1, 0,
            1, 3, 1, 0, 1,
            2, 3, 1, 1, 1,
            2, 3, 0, 1, 0,
            1, 3, 1, 0, 1,
        },
        {
            2, 3, 0, 0, 0,
            3, 3, 0, 1, 0,
            2, 3, 1, 0, 1,
            3, 3, 1, 1, 1,
            3, 3, 0, 1, 0,
            2, 3, 1, 0, 1,
        },
    },
    //second line
    {
        {
            0, 3, 1, 0, 0,
            1, 3, 1, 1, 0,
            0, 3, 2, 0, 1,
            1, 3, 2, 1, 1,
            1, 3, 1, 1, 0,
            0, 3, 2, 0, 1,
        },
        {
            1, 3, 1, 0, 0,
            2, 3, 1, 1, 0,
            1, 3, 2, 0, 1,
            2, 3, 2, 1, 1,
            2, 3, 1, 1, 0,
            1, 3, 2, 0, 1,
        },
        {
            2, 3, 1, 0, 0,
            3, 3, 1, 1, 0,
            2, 3, 2, 0, 1,
            3, 3, 2, 1, 1,
            3, 3, 1, 1, 0,
            2, 3, 2, 0, 1,
        },
    },
    //third line
    {
        {
            0, 3, 2, 0, 0,
            1, 3, 2, 1, 0,
            0, 3, 3, 0, 1,
            1, 3, 3, 1, 1,
            1, 3, 2, 1, 0,
            0, 3, 3, 0, 1,
        },
        {
            1, 3, 2, 0, 0,
            2, 3, 2, 1, 0,
            1, 3, 3, 0, 1,
            2, 3, 3, 1, 1,
            2, 3, 2, 1, 0,
            1, 3, 3, 0, 1,
        },
        {
            2, 3, 2, 0, 0,
            3, 3, 2, 1, 0,
            2, 3, 3, 0, 1,
            3, 3, 3, 1, 1,
            3, 3, 2, 1, 0,
            2, 3, 3, 0, 1,
        },
    },
},

//orange
{
    //first line
    {
        {
            0, 0, 2, 0, 0,
            0, 1, 2, 1, 0,
            0, 0, 3, 0, 1,
            0, 1, 3, 1, 1,
            0, 1, 2, 1, 0,
            0, 0, 3, 0, 1,
        },
        {
            0, 1, 2, 0, 0,
            0, 2, 2, 1, 0,
            0, 1, 3, 0, 1,
            0, 2, 3, 1, 1,
            0, 2, 2, 1, 0,
            0, 1, 3, 0, 1,
        },
        {
            0, 2, 2, 0, 0,
            0, 3, 2, 1, 0,
            0, 2, 3, 0, 1,
            0, 3, 3, 1, 1,
            0, 3, 2, 1, 0,
            0, 2, 3, 0, 1,
        },
    },
    //second line
    {
        {
            0, 0, 1, 0, 0,
            0, 1, 1, 1, 0,
            0, 0, 2, 0, 1,
            0, 1, 2, 1, 1,
            0, 1, 1, 1, 0,
            0, 0, 2, 0, 1,
        },
        {
            0, 1, 1, 0, 0,
            0, 2, 1, 1, 0,
            0, 1, 2, 0, 1,
            0, 2, 2, 1, 1,
            0, 2, 1, 1, 0,
            0, 1, 2, 0, 1,
        },
        {
            0, 2, 1, 0, 0,
            0, 3, 1, 1, 0,
            0, 2, 2, 0, 1,
            0, 3, 2, 1, 1,
            0, 3, 1, 1, 0,
            0, 2, 2, 0, 1,
        },
    },
    //third line
    {
        {
            0, 0, 0, 0, 0,
            0, 1, 0, 1, 0,
            0, 0, 1, 0, 1,
            0, 1, 1, 1, 1,
            0, 1, 0, 1, 0,
            0, 0, 1, 0, 1,
        },
        {
            0, 1, 0, 0, 0,
            0, 2, 0, 1, 0,
            0, 1, 1, 0, 1,
            0, 2, 1, 1, 1,
            0, 2, 0, 1, 0,
            0, 1, 1, 0, 1,
        },
        {
            0, 2, 0, 0, 0,
            0, 3, 0, 1, 0,
            0, 2, 1, 0, 1,
            0, 3, 1, 1, 1,
            0, 3, 0, 1, 0,
            0, 2, 1, 0, 1,
        },
    },
},

//red
{
    //first line
    {
        {
            3, 0, 2, 0, 0,
            3, 1, 2, 1, 0,
            3, 0, 3, 0, 1,
            3, 1, 3, 1, 1,
            3, 1, 2, 1, 0,
            3, 0, 3, 0, 1,
        },
        {
            3, 1, 2, 0, 0,
            3, 2, 2, 1, 0,
            3, 1, 3, 0, 1,
            3, 2, 3, 1, 1,
            3, 2, 2, 1, 0,
            3, 1, 3, 0, 1,
        },
        {
            3, 2, 2, 0, 0,
            3, 3, 2, 1, 0,
            3, 2, 3, 0, 1,
            3, 3, 3, 1, 1,
            3, 3, 2, 1, 0,
            3, 2, 3, 0, 1,
        },
    },
    //second line
    {
        {
            3, 0, 1, 0, 0,
            3, 1, 1, 1, 0,
            3, 0, 2, 0, 1,
            3, 1, 2, 1, 1,
            3, 1, 1, 1, 0,
            3, 0, 2, 0, 1,
        },
        {
            3, 1, 1, 0, 0,
            3, 2, 1, 1, 0,
            3, 1, 2, 0, 1,
            3, 2, 2, 1, 1,
            3, 2, 1, 1, 0,
            3, 1, 2, 0, 1,
        },
        {
            3, 2, 1, 0, 0,
            3, 3, 1, 1, 0,
            3, 2, 2, 0, 1,
            3, 3, 2, 1, 1,
            3, 3, 1, 1, 0,
            3, 2, 2, 0, 1,
        },
    },
    //third line
    {
        {
            3, 0, 0, 0, 0,
            3, 1, 0, 1, 0,
            3, 0, 1, 0, 1,
            3, 1, 1, 1, 1,
            3, 1, 0, 1, 0,
            3, 0, 1, 0, 1,
        },
        {
            3, 1, 0, 0, 0,
            3, 2, 0, 1, 0,
            3, 1, 1, 0, 1,
            3, 2, 1, 1, 1,
            3, 2, 0, 1, 0,
            3, 1, 1, 0, 1,
        },
        {
            3, 2, 0, 0, 0,
            3, 3, 0, 1, 0,
            3, 2, 1, 0, 1,
            3, 3, 1, 1, 1,
            3, 3, 0, 1, 0,
            3, 2, 1, 0, 1,
        },
    },
},
};