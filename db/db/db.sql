PGDMP  +    (            
    |            postgres    16.3    16.3 G    R           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            S           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            T           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            U           1262    5    postgres    DATABASE     |   CREATE DATABASE postgres WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Russian_Russia.1251';
    DROP DATABASE postgres;
                postgres    false            V           0    0    DATABASE postgres    COMMENT     N   COMMENT ON DATABASE postgres IS 'default administrative connection database';
                   postgres    false    4949                        2615    2200    public    SCHEMA        CREATE SCHEMA public;
    DROP SCHEMA public;
                pg_database_owner    false            W           0    0    SCHEMA public    COMMENT     6   COMMENT ON SCHEMA public IS 'standard public schema';
                   pg_database_owner    false    6            �            1259    17380 
   accounting    TABLE     �   CREATE TABLE public.accounting (
    id bigint NOT NULL,
    store_id bigint NOT NULL,
    product_article bigint NOT NULL,
    cost numeric(6,2),
    amount integer DEFAULT 0 NOT NULL
);
    DROP TABLE public.accounting;
       public         heap    postgres    false    6            �            1259    17377    accounting_id_seq    SEQUENCE     z   CREATE SEQUENCE public.accounting_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 (   DROP SEQUENCE public.accounting_id_seq;
       public          postgres    false    6    248            X           0    0    accounting_id_seq    SEQUENCE OWNED BY     G   ALTER SEQUENCE public.accounting_id_seq OWNED BY public.accounting.id;
          public          postgres    false    245            �            1259    17379    accounting_product_article_seq    SEQUENCE     �   CREATE SEQUENCE public.accounting_product_article_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 5   DROP SEQUENCE public.accounting_product_article_seq;
       public          postgres    false    248    6            Y           0    0    accounting_product_article_seq    SEQUENCE OWNED BY     a   ALTER SEQUENCE public.accounting_product_article_seq OWNED BY public.accounting.product_article;
          public          postgres    false    247            �            1259    17378    accounting_store_id_seq    SEQUENCE     �   CREATE SEQUENCE public.accounting_store_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 .   DROP SEQUENCE public.accounting_store_id_seq;
       public          postgres    false    248    6            Z           0    0    accounting_store_id_seq    SEQUENCE OWNED BY     S   ALTER SEQUENCE public.accounting_store_id_seq OWNED BY public.accounting.store_id;
          public          postgres    false    246            �            1259    16603    characterlists_seq    SEQUENCE     |   CREATE SEQUENCE public.characterlists_seq
    START WITH 1
    INCREMENT BY 50
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 )   DROP SEQUENCE public.characterlists_seq;
       public          postgres    false    6            �            1259    17365 
   check_list    TABLE     �   CREATE TABLE public.check_list (
    id bigint NOT NULL,
    store_id bigint NOT NULL,
    "time" timestamp without time zone NOT NULL
);
    DROP TABLE public.check_list;
       public         heap    postgres    false    6            �            1259    17363    check_list_id_seq    SEQUENCE     z   CREATE SEQUENCE public.check_list_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 (   DROP SEQUENCE public.check_list_id_seq;
       public          postgres    false    6    244            [           0    0    check_list_id_seq    SEQUENCE OWNED BY     G   ALTER SEQUENCE public.check_list_id_seq OWNED BY public.check_list.id;
          public          postgres    false    242            �            1259    17364    check_list_store_id_seq    SEQUENCE     �   CREATE SEQUENCE public.check_list_store_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 .   DROP SEQUENCE public.check_list_store_id_seq;
       public          postgres    false    244    6            \           0    0    check_list_store_id_seq    SEQUENCE OWNED BY     S   ALTER SEQUENCE public.check_list_store_id_seq OWNED BY public.check_list.store_id;
          public          postgres    false    243            �            1259    17357    product    TABLE     �   CREATE TABLE public.product (
    article bigint NOT NULL,
    name character varying(100) NOT NULL,
    category character varying(10),
    quantity_to_assess character varying(10) NOT NULL
);
    DROP TABLE public.product;
       public         heap    postgres    false    6            �            1259    17356    product_article_seq    SEQUENCE     |   CREATE SEQUENCE public.product_article_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 *   DROP SEQUENCE public.product_article_seq;
       public          postgres    false    241    6            ]           0    0    product_article_seq    SEQUENCE OWNED BY     K   ALTER SEQUENCE public.product_article_seq OWNED BY public.product.article;
          public          postgres    false    240            �            1259    17402    purchase    TABLE     �   CREATE TABLE public.purchase (
    id bigint NOT NULL,
    check_list_id bigint NOT NULL,
    product_article bigint NOT NULL,
    amount numeric(6,3) NOT NULL
);
    DROP TABLE public.purchase;
       public         heap    postgres    false    6            �            1259    17400    purchase_check_list_id_seq    SEQUENCE     �   CREATE SEQUENCE public.purchase_check_list_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 1   DROP SEQUENCE public.purchase_check_list_id_seq;
       public          postgres    false    252    6            ^           0    0    purchase_check_list_id_seq    SEQUENCE OWNED BY     Y   ALTER SEQUENCE public.purchase_check_list_id_seq OWNED BY public.purchase.check_list_id;
          public          postgres    false    250            �            1259    17399    purchase_id_seq    SEQUENCE     x   CREATE SEQUENCE public.purchase_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 &   DROP SEQUENCE public.purchase_id_seq;
       public          postgres    false    6    252            _           0    0    purchase_id_seq    SEQUENCE OWNED BY     C   ALTER SEQUENCE public.purchase_id_seq OWNED BY public.purchase.id;
          public          postgres    false    249            �            1259    17401    purchase_product_article_seq    SEQUENCE     �   CREATE SEQUENCE public.purchase_product_article_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 3   DROP SEQUENCE public.purchase_product_article_seq;
       public          postgres    false    252    6            `           0    0    purchase_product_article_seq    SEQUENCE OWNED BY     ]   ALTER SEQUENCE public.purchase_product_article_seq OWNED BY public.purchase.product_article;
          public          postgres    false    251            �            1259    17350    store    TABLE     Z   CREATE TABLE public.store (
    id bigint NOT NULL,
    address character varying(100)
);
    DROP TABLE public.store;
       public         heap    postgres    false    6            �            1259    17349    store_id_seq    SEQUENCE     u   CREATE SEQUENCE public.store_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 #   DROP SEQUENCE public.store_id_seq;
       public          postgres    false    6    239            a           0    0    store_id_seq    SEQUENCE OWNED BY     =   ALTER SEQUENCE public.store_id_seq OWNED BY public.store.id;
          public          postgres    false    238            �            1259    16604 	   users_seq    SEQUENCE     s   CREATE SEQUENCE public.users_seq
    START WITH 1
    INCREMENT BY 50
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
     DROP SEQUENCE public.users_seq;
       public          postgres    false    6            �           2604    17383    accounting id    DEFAULT     n   ALTER TABLE ONLY public.accounting ALTER COLUMN id SET DEFAULT nextval('public.accounting_id_seq'::regclass);
 <   ALTER TABLE public.accounting ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    248    245    248            �           2604    17384    accounting store_id    DEFAULT     z   ALTER TABLE ONLY public.accounting ALTER COLUMN store_id SET DEFAULT nextval('public.accounting_store_id_seq'::regclass);
 B   ALTER TABLE public.accounting ALTER COLUMN store_id DROP DEFAULT;
       public          postgres    false    246    248    248            �           2604    17385    accounting product_article    DEFAULT     �   ALTER TABLE ONLY public.accounting ALTER COLUMN product_article SET DEFAULT nextval('public.accounting_product_article_seq'::regclass);
 I   ALTER TABLE public.accounting ALTER COLUMN product_article DROP DEFAULT;
       public          postgres    false    247    248    248            �           2604    17368    check_list id    DEFAULT     n   ALTER TABLE ONLY public.check_list ALTER COLUMN id SET DEFAULT nextval('public.check_list_id_seq'::regclass);
 <   ALTER TABLE public.check_list ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    242    244    244            �           2604    17369    check_list store_id    DEFAULT     z   ALTER TABLE ONLY public.check_list ALTER COLUMN store_id SET DEFAULT nextval('public.check_list_store_id_seq'::regclass);
 B   ALTER TABLE public.check_list ALTER COLUMN store_id DROP DEFAULT;
       public          postgres    false    244    243    244            �           2604    17360    product article    DEFAULT     r   ALTER TABLE ONLY public.product ALTER COLUMN article SET DEFAULT nextval('public.product_article_seq'::regclass);
 >   ALTER TABLE public.product ALTER COLUMN article DROP DEFAULT;
       public          postgres    false    241    240    241            �           2604    17405    purchase id    DEFAULT     j   ALTER TABLE ONLY public.purchase ALTER COLUMN id SET DEFAULT nextval('public.purchase_id_seq'::regclass);
 :   ALTER TABLE public.purchase ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    249    252    252            �           2604    17406    purchase check_list_id    DEFAULT     �   ALTER TABLE ONLY public.purchase ALTER COLUMN check_list_id SET DEFAULT nextval('public.purchase_check_list_id_seq'::regclass);
 E   ALTER TABLE public.purchase ALTER COLUMN check_list_id DROP DEFAULT;
       public          postgres    false    252    250    252            �           2604    17407    purchase product_article    DEFAULT     �   ALTER TABLE ONLY public.purchase ALTER COLUMN product_article SET DEFAULT nextval('public.purchase_product_article_seq'::regclass);
 G   ALTER TABLE public.purchase ALTER COLUMN product_article DROP DEFAULT;
       public          postgres    false    252    251    252            �           2604    17353    store id    DEFAULT     d   ALTER TABLE ONLY public.store ALTER COLUMN id SET DEFAULT nextval('public.store_id_seq'::regclass);
 7   ALTER TABLE public.store ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    238    239    239            K          0    17380 
   accounting 
   TABLE DATA           Q   COPY public.accounting (id, store_id, product_article, cost, amount) FROM stdin;
    public          postgres    false    248   \N       G          0    17365 
   check_list 
   TABLE DATA           :   COPY public.check_list (id, store_id, "time") FROM stdin;
    public          postgres    false    244   �N       D          0    17357    product 
   TABLE DATA           N   COPY public.product (article, name, category, quantity_to_assess) FROM stdin;
    public          postgres    false    241   O       O          0    17402    purchase 
   TABLE DATA           N   COPY public.purchase (id, check_list_id, product_article, amount) FROM stdin;
    public          postgres    false    252   �O       B          0    17350    store 
   TABLE DATA           ,   COPY public.store (id, address) FROM stdin;
    public          postgres    false    239   EP       b           0    0    accounting_id_seq    SEQUENCE SET     @   SELECT pg_catalog.setval('public.accounting_id_seq', 50, true);
          public          postgres    false    245            c           0    0    accounting_product_article_seq    SEQUENCE SET     M   SELECT pg_catalog.setval('public.accounting_product_article_seq', 1, false);
          public          postgres    false    247            d           0    0    accounting_store_id_seq    SEQUENCE SET     F   SELECT pg_catalog.setval('public.accounting_store_id_seq', 1, false);
          public          postgres    false    246            e           0    0    characterlists_seq    SEQUENCE SET     B   SELECT pg_catalog.setval('public.characterlists_seq', 101, true);
          public          postgres    false    236            f           0    0    check_list_id_seq    SEQUENCE SET     @   SELECT pg_catalog.setval('public.check_list_id_seq', 1, false);
          public          postgres    false    242            g           0    0    check_list_store_id_seq    SEQUENCE SET     F   SELECT pg_catalog.setval('public.check_list_store_id_seq', 1, false);
          public          postgres    false    243            h           0    0    product_article_seq    SEQUENCE SET     B   SELECT pg_catalog.setval('public.product_article_seq', 1, false);
          public          postgres    false    240            i           0    0    purchase_check_list_id_seq    SEQUENCE SET     I   SELECT pg_catalog.setval('public.purchase_check_list_id_seq', 1, false);
          public          postgres    false    250            j           0    0    purchase_id_seq    SEQUENCE SET     >   SELECT pg_catalog.setval('public.purchase_id_seq', 36, true);
          public          postgres    false    249            k           0    0    purchase_product_article_seq    SEQUENCE SET     K   SELECT pg_catalog.setval('public.purchase_product_article_seq', 1, false);
          public          postgres    false    251            l           0    0    store_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.store_id_seq', 1, false);
          public          postgres    false    238            m           0    0 	   users_seq    SEQUENCE SET     9   SELECT pg_catalog.setval('public.users_seq', 201, true);
          public          postgres    false    237            �           2606    17388    accounting accounting_pkey 
   CONSTRAINT     X   ALTER TABLE ONLY public.accounting
    ADD CONSTRAINT accounting_pkey PRIMARY KEY (id);
 D   ALTER TABLE ONLY public.accounting DROP CONSTRAINT accounting_pkey;
       public            postgres    false    248            �           2606    17371    check_list check_list_pkey 
   CONSTRAINT     X   ALTER TABLE ONLY public.check_list
    ADD CONSTRAINT check_list_pkey PRIMARY KEY (id);
 D   ALTER TABLE ONLY public.check_list DROP CONSTRAINT check_list_pkey;
       public            postgres    false    244            �           2606    17362    product product_pkey 
   CONSTRAINT     W   ALTER TABLE ONLY public.product
    ADD CONSTRAINT product_pkey PRIMARY KEY (article);
 >   ALTER TABLE ONLY public.product DROP CONSTRAINT product_pkey;
       public            postgres    false    241            �           2606    17409    purchase purchase_pkey 
   CONSTRAINT     T   ALTER TABLE ONLY public.purchase
    ADD CONSTRAINT purchase_pkey PRIMARY KEY (id);
 @   ALTER TABLE ONLY public.purchase DROP CONSTRAINT purchase_pkey;
       public            postgres    false    252            �           2606    17355    store store_pkey 
   CONSTRAINT     N   ALTER TABLE ONLY public.store
    ADD CONSTRAINT store_pkey PRIMARY KEY (id);
 :   ALTER TABLE ONLY public.store DROP CONSTRAINT store_pkey;
       public            postgres    false    239            �           2606    17394 *   accounting accounting_product_article_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.accounting
    ADD CONSTRAINT accounting_product_article_fkey FOREIGN KEY (product_article) REFERENCES public.product(article) ON DELETE CASCADE;
 T   ALTER TABLE ONLY public.accounting DROP CONSTRAINT accounting_product_article_fkey;
       public          postgres    false    241    248    4772            �           2606    17389 #   accounting accounting_store_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.accounting
    ADD CONSTRAINT accounting_store_id_fkey FOREIGN KEY (store_id) REFERENCES public.store(id) ON DELETE CASCADE;
 M   ALTER TABLE ONLY public.accounting DROP CONSTRAINT accounting_store_id_fkey;
       public          postgres    false    248    239    4770            �           2606    17372 #   check_list check_list_store_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.check_list
    ADD CONSTRAINT check_list_store_id_fkey FOREIGN KEY (store_id) REFERENCES public.store(id) ON DELETE SET NULL;
 M   ALTER TABLE ONLY public.check_list DROP CONSTRAINT check_list_store_id_fkey;
       public          postgres    false    244    239    4770            �           2606    17410 $   purchase purchase_check_list_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.purchase
    ADD CONSTRAINT purchase_check_list_id_fkey FOREIGN KEY (check_list_id) REFERENCES public.check_list(id) ON DELETE CASCADE;
 N   ALTER TABLE ONLY public.purchase DROP CONSTRAINT purchase_check_list_id_fkey;
       public          postgres    false    252    4774    244            �           2606    17415 &   purchase purchase_product_article_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.purchase
    ADD CONSTRAINT purchase_product_article_fkey FOREIGN KEY (product_article) REFERENCES public.product(article) ON DELETE CASCADE;
 P   ALTER TABLE ONLY public.purchase DROP CONSTRAINT purchase_product_article_fkey;
       public          postgres    false    252    4772    241            K   [   x�E�� !D�3cP`]z����c4����e�f&�Lc`��� �ہ �x!�+�Sa���N�u*/W�
����l���T�Y��      G   D   x�}˱� �ڞ"��χ fa�9��D�>Ơ
P43T��87�[f2�������g^��_ʒ"      D   �   x�5�;�`���O���qL�1HB�

b�6� ��+���]�Mf����g�P��J��ȖS�Ȣ�uAQ���sݍ�n�s���W�%j�O��9GC�vRl��, ��E��Bt�i=trA8q�$Ǜ�������0p�ݩT5h%�.@�^xk��������y�      O   [   x�=�K� C��0��.��9�v��A�18�C�iP*�tI��-�
+X)��<6��ê���)3�}��g��U���&&/e{zk��!�      B   (   x�3��q�Q0Up,K�+M�2sa|c�Ə���� Om�     