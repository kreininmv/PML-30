/* FILE NAME   : PRIMITIVE.H
 * PURPOSE     : Primitive system.
 *               HeaderModule.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __PRIM_H_
#define __PRIM_H_

#include "RESMANAGER.H"
#include "MATERIAL.H"

namespace mk5
{
  class vertex
  {
  public:
    vec P;  // Vertex position
    vec2 T; // Vertex texture coordinates
    vec N;  // Vertex normal
    vec4 C; // Vertex color

    vertex( VOID )
    {
    }

    /* Class constructor.
     * ARGUMENTS:
     *   - new vertex position:
     *       const vec &NewP;
     *   - new vertex texture coordinates:
     *       const vec2 &NewT;
     *   - new vertex normal:
     *       const vec &NewN;
     *   - new vertex color:
     *       const vec4 &NewC;
     */
    vertex( const vec &NewP,
      const vec2 &NewT = vec2(0, 0),
      const vec &NewN = vec(0, 1, 0),
      const vec4 &NewC = vec4(1) ) :
      P(NewP), T(NewT), N(NewN), C(NewC)
    {
    } /* End of 'VERTEX' function */
  };
    class prim;

    /* Base topology class */
    class base
    {
    public:

      enum type
      {
        POINT, MESH, STRIP, LINE, LINESTRIP
      };

      type Type = type::MESH;

      /* Vertex array */
      std::vector<vertex> V;
      /* Index array */
      std::vector<INT> I;

      /* Class default constructor */
      base( VOID )
      {
      } /* End of 'base' function */

        /* Class constructor.
        * ARGUMENTS:
        *   - primitive type:
        *       prim::type NewType;
        *   - vertex array:
        *       const std::vector<prim::VERTEX> &NewV;
        *   - index array:
        *       const std::vector<INT> &NewI;
        */
      base( type NewType,
        const std::vector<vertex> &NewV = {},
        const std::vector<INT> &NewI = {} ) : Type(NewType), V(NewV), I(NewI)
      {
      } /* End of 'base' function */

    };

    /* Trimesh topology class */
    class trimesh : public base
    {
    public:
      /* Class default constructor */
      trimesh( VOID )
      {
      } /* End of 'trimesh' function */

        /* Class constructor.
        * ARGUMENTS:
        *   - vertex array:
        *       const std::vector<prim::VERTEX> &NewV;
        *   - index array:
        *       const std::vector<INT> &NewI;
        */
      trimesh( const std::vector<vertex> &NewV,
        const std::vector<INT> &NewI = {} ) : base(type::MESH, NewV, NewI)
      {
      } /* End of 'trimesh' function */

        /* Evaluate trimesh vertex normals function.
        * ARGUMENTS: None.
        * RETURNS: None.
        */
      VOID EvalNormals( VOID )
      {
        /* Set to zero all normals */
        for (auto &v : V)
          v.N = vec(0);

        /* Evaluate all facets normals */
        for (INT i = 0; i < I.size(); i += 3)
        {
          vertex *p0 = &V[I[i]], *p1 = &V[I[i + 1]], *p2 = &V[I[i + 2]];
          vec N = (p1->P - p0->P) % (p2->P - p0->P);
          N.Normalize();

          /* Disperse normal to all three points */
          p0->N += N;
          p1->N += N;
          p2->N += N;
        }

        /* Normalize all normals */
        for (auto &v : V)
          v.N.Normalize();
      } /* End of 'EvalNormals' function */
    }; /* End of 'trimesh' class */

       /* Grid topology class */
    class grid : public base
    {
    protected:
      /* Grid size */
      INT W, H;

    public:
      /* Class default constructor */
      grid( VOID )
      {
      } /* End of 'grid' function */

        /* Class constructor.
        * ARGUMENTS:
        *   - grid size:
        *       INT NewW, NewH;
        */
      grid( INT NewW, INT NewH ) : W(NewW), H(NewH), base(type::STRIP)
      {
        /* Setup vertices */
        V.resize(W * H, vertex(vec(0), vec2(0), vec(0), vec4(1)));
        /* Setup vertices */
        auto p = V.begin();
        for (INT i = 0; i < H; i++)
          for (INT j = 0; j < W; j++, p++)
            p->T = vec2(j / (W - 1.0), i / (H - 1.0));

        /* Setup indices */
        I.resize((W * 2 + 1) * (H - 1));
        for (INT k = 0, v = 0, i = 0; i < H - 1; i++)
        {
          for (INT j = 0; j < W; j++, v++)
          {
            I[k++] = v + W;
            I[k++] = v;
          }
          I[k++] = -1;
        }
      } /* End of 'grid' function */

        /* Obtain grid width function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (INT) grid width.
        */
      INT GetW( VOID ) const
      {
        return W;
      } /* End of 'GetW' function */

        /* Obtain grid height function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (INT) grid height.
        */
      INT GetH( VOID ) const
      {
        return H;
      } /* End of 'GetH' function */

        /* Grid 2D array vertex access function.
        * ARGUMENTS:
        *   - row index:
        *       INT Row;
        * RETURNS:
        *   (prim::VERTEX *) vertex row pointer.
        */
      vertex* operator[]( INT Row )
      {
        return &V[Row * W];
      } /* End of 'operator[]' function */

        /* Evaluate grid vertex normals function.
        * ARGUMENTS: None.
        * RETURNS: None.
        */
      VOID EvalNormals( VOID )
      {
        /* Set to zero all normals */
        for (auto &v : V)
          v.N = vec(0);

        /* Evaluate all facets normals */
        for (INT k = 0, i = 0; i < H - 1; i++)
          for (INT j = 0; j < W - 1; j++, k++)
          {
            vertex
              *p00 = &V[k],
              *p10 = &V[k + W],
              *p01 = &V[k + 1],
              *p11 = &V[k + W + 1];
            vec
              N1 = (p00->P - p10->P) % (p11->P - p10->P),
              N2 = (p11->P - p01->P) % (p00->P - p01->P);
            N1.Normalize();
            N2.Normalize();

            /* Disperse normal to all three points */
            p10->N += N1;
            p00->N += N1;
            p11->N += N1;

            p00->N += N2;
            p01->N += N2;
            p11->N += N2;
          }

        /* Normalize all normals */
        for (auto &v : V)
          v.N.Normalize();
      } /* End of 'EvalNormals' function */
    }; /* End of 'grid' class */

       /* Sphere topology class */
    class sphere : public grid
    {
    public:
      /* Class default constructor */
      sphere( VOID )
      {
      } /* End of 'sphere' function */

        /* Class constructor.
        * ARGUMENTS:
        *   - sphere center:
        *       const vec &Center;
        *   - sphere radius:
        *       FLT R;
        *   - grid size:
        *       INT NewW, NewH;
        */
      sphere( vec Center, FLT R, INT NewW = 50, INT NewH = 23 ) : grid(NewW, NewH)
      {
        /* Setup vertices */
        auto p = V.begin();
        INT i, j;
        FLT theta, phi;
        for (theta = 0, i = 0; i < H; i++, theta += mth::PI / (H - 1))
          for (phi = 0, j = 0; j < W; j++, phi += 2 * mth::PI / (W - 1), p++)
          {
            p->N = vec(sin(theta) * sin(phi), cos(theta), sin(theta) * cos(phi));
            p->P = Center + (p->N * R);
          }
      } /* End of 'sphere' function */
    }; /* End of 'sphere' class */

    /* Sphere topology class */
    class plane : public grid
    {
    public:
      /* Class default constructor */
      plane( VOID )
      {
      } /* End of 'sphere' function */

        /* Class constructor.
        * ARGUMENTS:
        *   - plane corner:
        *       const vec &Corner;
        *   - plane directions:
        *       const vec &Du, &Dv;
        *   - grid size:
        *       INT NewW, NewH;
        */
      plane( const vec &Corner, const vec &Du, const vec &Dv, INT NewW = 50, INT NewH = 50 ) :
        grid(NewW, NewH)
      {
        vec N = Du % Dv;
        N.Normalize();

        /* Setup vertices */
        auto p = V.begin();
        for (INT i = 0; i < H; i++)
          for (INT j = 0; j < W; j++, p++)
          {
            p->N = N;
            p->P = Corner + Du * j / (W - 1.0) + Dv * i / (H - 1.0);
          }
      } /* End of 'plane' function */
    }; /* End of 'plane' class */

       /* Primitives class */
    class prim
    {
    public:
      static resource_manager<prim> Primitives; /* Primitives manager */

      std::string Name;

      /* Primitives type */
      base::type TYPE;

      UINT VA, VBuf, IBuf = 0, VertexCount;

      material *mtl;

      /* Primitive constructor.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
      prim( VOID )
      {

      }

      /* Primitive constructor.
      * ARGUMENTS:
      *   - link to sting:
      *       const std::string &S;
      * RETURNS: None.
      */
      prim( const std::string &S ) : Name(S)
      {
        mtl = new material(S);
        mtl->Materials.Add(mtl);
      }


      prim( plane *Topo, const std::string &S ) : Name(S)
      {
        TYPE = base::type::STRIP;
        FromVertexArray(Topo->V.data(), Topo->V.size(), Topo->I.data(), Topo->I.size());
        mtl = new material(S);
        mtl->Materials.Add(mtl);
      }

      /* Primitive constructor.
       * ARGUMENTS:
       *   - link to sting:
       *       const std::string &S;
       * RETURNS: None.
       */
       prim( trimesh &Topo, const std::string &S ) : Name(S)
      {
        FromVertexArray(Topo.V.data(), Topo.V.size(), Topo.I.data(), Topo.I.size());
      }

      /* Primitive constructor.
       * ARGUMENTS:
       *   - link to sting:
       *       const std::string &S;
       * RETURNS: None.
       */
      prim( sphere *Topo, const std::string &S, float r ) : Name(S)
      {
        FromVertexArray(Topo->V.data(), Topo->V.size(), Topo->I.data(), Topo->I.size());
        mtl = new material(S);
        mtl->Materials.Add(mtl);
        TYPE = Topo->Type;
      }


      /* Primitive destructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      ~prim( VOID )
      {
      }

      /* Create primitive from topology function.
      * ARGUMENTS:
      *   - link to topology:
      *       topo &Topo;
      * RETURNS:
      *   (prim *) pointer to primitive.
      */
      prim * FromTopo( base &Topo );

      /* Create primitive from vertexes array function.
      * ARGUMENTS:
      *   - pointer to vertex array:
      *       vertex *V;
      *   - Count of vertexes:
      *       UINT NumOfVer;
      *   - pointer to index array:
      *       int *I;
      *   - Count of indexes:
      *       UINT NumOfI;
      * RETURNS:
      *   (prim *) pointer to primitive
      */
      prim * FromVertexArray( vertex *V, UINT NumOfVer, INT *I = nullptr, UINT NumOfI = 0 );

      /* Create primitive from file function.
      * ARGUMENTS:
      *   - file name:
      *       std::string &FileName;
      * RETURNS:
      *   (prim *) pointer to primitive.
      */
      prim * FromFile( CHAR *FileName );
    };
} /* End of 'mk5' namespace */

#endif /* __PRIM_H_*/

/* END OF 'PRIM.H' FILE */