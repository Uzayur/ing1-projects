package fr.epita.assistant.seq;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public interface Seq<ELEMENT_TYPE> extends ExtendedStream<ELEMENT_TYPE> {

    Stream<ELEMENT_TYPE> getStream();

    public static <TYPE> ExtendedStream<TYPE> of(final List<TYPE> values) {
        Seq<TYPE> seq = () -> values.stream();
       return seq;
    }

    public static <TYPE> Seq<TYPE> of(final TYPE... values) {
        Seq<TYPE> seq = () -> Stream.of(values);
        return seq;
    }

    public static <TYPE> Seq<TYPE> of(final Stream<TYPE> values) {
        Seq<TYPE> seq = () -> values;
        return seq;
    }

    @Override
    default <KEY_TYPE> Map<KEY_TYPE, ELEMENT_TYPE> toMap(final Function<ELEMENT_TYPE, KEY_TYPE> keyMapper) {
        return getStream().collect(Collectors.toMap(keyMapper, elt -> elt, (elt, b) -> b));
    }

    @Override
    default <KEY_TYPE, VALUE_TYPE, MAP_TYPE extends Map<KEY_TYPE, VALUE_TYPE>> MAP_TYPE toMap(final MAP_TYPE map, final Function<ELEMENT_TYPE, KEY_TYPE> keyMapper, final Function<ELEMENT_TYPE, VALUE_TYPE> valueMapper) {
        getStream().forEach(e -> map.put(keyMapper.apply(e), valueMapper.apply(e)));
        return map;
    }

    @Override
    default <KEY_TYPE, VALUE_TYPE> Map<KEY_TYPE, VALUE_TYPE> toMap(final Function<ELEMENT_TYPE, KEY_TYPE> keyMapper, final Function<ELEMENT_TYPE, VALUE_TYPE> valueMapper) {
        return getStream().collect(Collectors.toMap(keyMapper, valueMapper, (elt, b) -> b));
    }

    @Override
    default List<ELEMENT_TYPE> toList() {
        return getStream().toList();
    }

    @Override
    default <LIST extends List<ELEMENT_TYPE>> LIST toList(final LIST list) {
        list.addAll(getStream().toList());
        return list;
    }

    @Override
    default Set<ELEMENT_TYPE> toSet() {
        return getStream().collect(Collectors.toSet());
    }

    @Override
    default <SET extends Set<ELEMENT_TYPE>> SET toSet(final SET set) {
        set.addAll(getStream().collect(Collectors.toSet()));
        return set;
    }

    @Override
    default <ASSOCIATED_TYPE> Seq<Pair<ELEMENT_TYPE, ASSOCIATED_TYPE>> associate(final Supplier<ASSOCIATED_TYPE> supplier) {
        return of(getStream().map(s->new Pair<ELEMENT_TYPE, ASSOCIATED_TYPE>(s, supplier.get())));
    }

    @Override
    default <ASSOCIATED_TYPE> Seq<Pair<ELEMENT_TYPE, ASSOCIATED_TYPE>> associate(final Stream<ASSOCIATED_TYPE> supplier) {
        var list1 = getStream().toList();
        var list2 = supplier.toList();

        var list = new ArrayList<Pair<ELEMENT_TYPE, ASSOCIATED_TYPE>>();

        for (var index = 0; index < Math.min(list1.size(), list2.size()); index++)
            list.add(new Pair<ELEMENT_TYPE, ASSOCIATED_TYPE>(list1.get(index), list2.get(index)));

        return (Seq<Pair<ELEMENT_TYPE, ASSOCIATED_TYPE>>) Seq.of(list);
    }

    @Override
    default Seq<ELEMENT_TYPE> print() {
        getStream().forEach(elt -> System.out.println(elt));
        return null;
    }

    @Override
    default ExtendedStream<ELEMENT_TYPE> plus(final Stream<ELEMENT_TYPE> stream) {
        var list = getStream().collect(Collectors.toList());
        var list2 = stream.toList();

        return (ExtendedStream<ELEMENT_TYPE>) Seq.of(list, list2);
    }

    @Override
    default Object join(final String delimiter) {
        return getStream().collect(Collectors.toList()).toString().replace("[", "").replace("]", "").replace(", ", delimiter);
    }

    @Override
    default String join() {
        return getStream().collect(Collectors.toList()).toString().replace("[", "").replace("]", "").replace(" ", "").replace(",", "");
    }

    @Override
    default <KEY_TYPE> Seq<Pair<KEY_TYPE, ExtendedStream<ELEMENT_TYPE>>> partition(final Function<ELEMENT_TYPE, KEY_TYPE> pivot) {
        var listPair = new ArrayList<Pair<KEY_TYPE, ELEMENT_TYPE>>();
        var listDistinctPivot = new ArrayList<KEY_TYPE>();

        for (var value : getStream().toList()) {
            var newValue = pivot.apply(value);
            listPair.add(new Pair<KEY_TYPE, ELEMENT_TYPE>(newValue, value));
            if (!listDistinctPivot.contains(newValue))
                listDistinctPivot.add(newValue);
        }

        var returnList = new ArrayList<Pair<KEY_TYPE, ExtendedStream<ELEMENT_TYPE>>>();

        for (var value : listDistinctPivot) {
            var listExtendedStream = new ArrayList<ELEMENT_TYPE>();
            for (var tempValue : listPair) {
                if (tempValue.first.equals(value))
                    listExtendedStream.add((ELEMENT_TYPE) tempValue.second);
            }
            returnList.add(new Pair<KEY_TYPE, ExtendedStream<ELEMENT_TYPE>>(value, Seq.of(listExtendedStream)));
        }
        return (Seq<Pair<KEY_TYPE, ExtendedStream<ELEMENT_TYPE>>>) Seq.of(returnList);
    }


    @Override
    default Stream<ELEMENT_TYPE> filter(Predicate<? super ELEMENT_TYPE> predicate) {
        return null;
    }

    @Override
    default <R> Stream<R> map(Function<? super ELEMENT_TYPE, ? extends R> mapper) {
        return null;
    }

    @Override
    default IntStream mapToInt(ToIntFunction<? super ELEMENT_TYPE> mapper) {
        return null;
    }

    @Override
    default LongStream mapToLong(ToLongFunction<? super ELEMENT_TYPE> mapper) {
        return null;
    }

    @Override
    default DoubleStream mapToDouble(ToDoubleFunction<? super ELEMENT_TYPE> mapper) {
        return null;
    }

    @Override
    default <R> Stream<R> flatMap(Function<? super ELEMENT_TYPE, ? extends Stream<? extends R>> mapper) {
        return null;
    }

    @Override
    default IntStream flatMapToInt(Function<? super ELEMENT_TYPE, ? extends IntStream> mapper) {
        return null;
    }

    @Override
    default LongStream flatMapToLong(Function<? super ELEMENT_TYPE, ? extends LongStream> mapper) {
        return null;
    }

    @Override
    default DoubleStream flatMapToDouble(Function<? super ELEMENT_TYPE, ? extends DoubleStream> mapper) {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> distinct() {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> sorted() {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> sorted(Comparator<? super ELEMENT_TYPE> comparator) {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> peek(Consumer<? super ELEMENT_TYPE> action) {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> limit(long maxSize) {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> skip(long n) {
        return null;
    }

    @Override
    default void forEach(Consumer<? super ELEMENT_TYPE> action) {

    }

    @Override
    default void forEachOrdered(Consumer<? super ELEMENT_TYPE> action) {

    }

    @Override
    default Object[] toArray() {
        return new Object[0];
    }

    @Override
    default <A> A[] toArray(IntFunction<A[]> generator) {
        return null;
    }

    @Override
    default ELEMENT_TYPE reduce(ELEMENT_TYPE identity, BinaryOperator<ELEMENT_TYPE> accumulator) {
        return null;
    }

    @Override
    default Optional<ELEMENT_TYPE> reduce(BinaryOperator<ELEMENT_TYPE> accumulator) {
        return Optional.empty();
    }

    @Override
    default <U> U reduce(U identity, BiFunction<U, ? super ELEMENT_TYPE, U> accumulator, BinaryOperator<U> combiner) {
        return null;
    }

    @Override
    default <R> R collect(Supplier<R> supplier, BiConsumer<R, ? super ELEMENT_TYPE> accumulator, BiConsumer<R, R> combiner) {
        return null;
    }

    @Override
    default <R, A> R collect(Collector<? super ELEMENT_TYPE, A, R> collector) {
        return null;
    }

    @Override
    default Optional<ELEMENT_TYPE> min(Comparator<? super ELEMENT_TYPE> comparator) {
        return Optional.empty();
    }

    @Override
    default Optional<ELEMENT_TYPE> max(Comparator<? super ELEMENT_TYPE> comparator) {
        return Optional.empty();
    }

    @Override
    default long count() {
        return 0;
    }

    @Override
    default boolean anyMatch(Predicate<? super ELEMENT_TYPE> predicate) {
        return false;
    }

    @Override
    default boolean allMatch(Predicate<? super ELEMENT_TYPE> predicate) {
        return false;
    }

    @Override
    default boolean noneMatch(Predicate<? super ELEMENT_TYPE> predicate) {
        return false;
    }

    @Override
    default Optional<ELEMENT_TYPE> findFirst() {
        return Optional.empty();
    }

    @Override
    default Optional<ELEMENT_TYPE> findAny() {
        return Optional.empty();
    }

    @Override
    default Iterator<ELEMENT_TYPE> iterator() {
        return null;
    }

    @Override
    default Spliterator<ELEMENT_TYPE> spliterator() {
        return null;
    }

    @Override
    default boolean isParallel() {
        return false;
    }

    @Override
    default Stream<ELEMENT_TYPE> sequential() {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> parallel() {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> unordered() {
        return null;
    }

    @Override
    default Stream<ELEMENT_TYPE> onClose(Runnable closeHandler) {
        return null;
    }

    @Override
    default void close() {

    }
}